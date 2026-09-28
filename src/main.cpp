#include <Geode/Geode.hpp>
#include <Geode/modify/MusicDownloadManager.hpp>
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

class $modify(MyMusicManager, MusicDownloadManager) {
    void downloadSong(int songID) {
        log::info("Interceptando descarga de canción con ID: {}", songID);

        // 1. URL de tu Cloudflare Worker configurada para extraer el MP3
        std::string workerUrl = fmt::format(
            "https://newgrounds.polagest.workers.dev/audio/listen/{}", 
            songID
        );

        // 2. Ruta local donde Geometry Dash guarda las canciones descargadas
        ghc::filesystem::path songPath = this->getSongPath(songID);

        // 3. Petición HTTP usando la API de Geode
        web::WebRequest req = web::WebRequest();
        
        // Ejecutamos la descarga asíncrona hacia el Worker
        req.get(workerUrl).listen([this, songID, songPath](web::WebResponse* response) {
            if (response && response->ok()) {
                // Guardamos los datos del MP3 directamente en el disco
                auto bytes = response->data();
                if (file::writeBinary(songPath, bytes)) {
                    log::info("Canción {} descargada e instalada con éxito.", songID);
                    
                    // Notificamos al juego que la canción ya está lista
                    this->onDownloadSongCompleted(songID);
                } else {
                    log::error("Error al guardar el archivo MP3 en disco.");
                }
            } else {
                log::error("Error al conectar con el Worker para la canción {}.", songID);
            }
        });
    }
};
