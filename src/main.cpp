#include <Geode/Geode.hpp>
#include <Geode/modify/MusicDownloadManager.hpp>
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

class $modify(MyMusicManager, MusicDownloadManager) {
    void downloadSong(int songID) {
        log::info("Interceptando descarga de cancion ID: {}", songID);

        // URL de tu Worker
        std::string workerUrl = fmt::format(
            "https://newgrounds.polagest.workers.dev/audio/listen/{}", 
            songID
        );

        // Ruta local donde GD guarda la musica (GD/geode/resources/.../music/ID.mp3)
        auto musicDir = dirs::getGeodeDir() / "resources" / "music";
        std::filesystem::create_directories(musicDir);
        auto songPath = musicDir / fmt::format("{}.mp3", songID);

        // Peticion HTTP con la libreria de Geode
        web::WebRequest req = web::WebRequest();
        
        req.get(workerUrl).listen([this, songID, songPath](web::WebResponse* response) {
            if (response && response->ok()) {
                auto bytes = response->data();
                if (file::writeBinary(songPath, bytes)) {
                    log::info("Cancion {} guardada correctamente.", songID);
                    this->onDownloadSongCompleted(songID);
                } else {
                    log::error("Error escribiendo archivo MP3 en disco.");
                }
            } else {
                log::error("Error al conectar con el Worker.");
            }
        });
    }
};
