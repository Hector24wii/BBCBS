#include <Geode/Geode.hpp>
#include <Geode/modify/MusicDownloadManager.hpp>
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

class $modify(MyMusicManager, MusicDownloadManager) {
    void downloadSong(int songID) {
        log::info("Interceptando descarga de cancion ID: {}", songID);

        std::string workerUrl = fmt::format(
            "https://newgrounds.polagest.workers.dev/audio/listen/{}", 
            songID
        );

        // En Geode, pathForSong o el directorio de recursos se encarga del archivo local
        auto songPath = this->pathForSong(songID);

        // Realizar la peticion HTTP usando el task/listener de Geode
        web::WebRequest req;
        req.get(workerUrl).listen(
            [this, songID, songPath](web::WebResponse* res) {
                if (res && res->ok()) {
                    auto data = res->data();
                    if (file::writeBinary(songPath, data)) {
                        log::info("Cancion {} instalada.", songID);
                        this->onDownloadSongCompleted(songID);
                    } else {
                        log::error("Error al escribir el archivo.");
                    }
                } else {
                    log::error("Error en la peticion al Worker.");
                }
            }
        );
    }
};
