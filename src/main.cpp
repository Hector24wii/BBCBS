#include <Geode/Geode.hpp>
#include <Geode/modify/MusicDownloadManager.hpp>
#include <Geode/utils/web.hpp>
#include <filesystem>

using namespace geode::prelude;

class $modify(MyMusicManager, MusicDownloadManager) {
    void downloadSong(int songID) {
        log::info("Interceptando descarga de canción ID: {}", songID);

        // 1. URL de tu Worker
        std::string workerUrl = fmt::format(
            "https://newgrounds.polagest.workers.dev/audio/listen/{}", 
            songID
        );

        // 2. Ruta local estándar de la canción en Geode
        std::filesystem::path songPath = this->pathForSong(songID);

        // 3. Petición HTTP asíncrona
        web::WebRequest req = web::WebRequest();
        
        req.get(workerUrl).listen([this, songID, songPath](web::WebResponse* response) {
            if (response && response->ok()) {
                auto bytes = response->data();
                if (file::writeBinary(songPath, bytes)) {
                    log::info("Canción {} guardada con éxito.", songID);
                    this->onDownloadSongCompleted(songID);
                } else {
                    log::error("Error al escribir el archivo de música.");
                }
            } else {
                log::error("Error al conectar con el Worker para la canción {}.", songID);
            }
        });
    }
};
