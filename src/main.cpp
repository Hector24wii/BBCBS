#include <Geode/Geode.hpp>
#include <Geode/modify/MusicDownloadManager.hpp>
#include <Geode/utils/web.hpp>
#include <filesystem>

using namespace geode::prelude;

class $modify(MyMusicManager, MusicDownloadManager) {
    void downloadSong(int songID) {
        log::info("Interceptando descarga de cancion ID: {}", songID);

        // 1. URL de tu Cloudflare Worker
        std::string workerUrl = fmt::format(
            "https://newgrounds.polagest.workers.dev/audio/listen/{}", 
            songID
        );

        // 2. Obtener la ruta para guardar la canción (.mp3)
        std::filesystem::path songPath = Mod::get()->getSaveDir() / fmt::format("{}.mp3", songID);

        // 3. Petición HTTP usando la API de Geode
        web::WebRequest req = web::WebRequest();
        
        req.get(workerUrl).listen([this, songID, songPath](web::WebResponse* response) {
            if (response && response->ok()) {
                auto bytes = response->data();
                if (file::writeBinary(songPath, bytes)) {
                    log::info("Cancion {} guardada exitosamente.", songID);
                    this->onDownloadSongCompleted(songID);
                } else {
                    log::error("No se pudo escribir el archivo MP3.");
                }
            } else {
                log::error("Error al conectar con el Worker para la cancion {}.", songID);
            }
        });
    }
};
