#include <Geode/Geode.hpp>
#include <Geode/modify/MusicDownloadManager.hpp>
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

// Almacena los listeners globales para evitar que las peticiones asíncronas se cancelen prematuramente
static std::vector<EventListener<web::WebTask>*> g_activeListeners;

class $modify(MyMusicManager, MusicDownloadManager) {
    void downloadSong(int songID) {
        log::info("Interceptando descarga de canción ID: {}", songID);

        std::string workerUrl = fmt::format(
            "https://newgrounds.polagest.workers.dev/audio/listen/{}", 
            songID
        );

        auto songPath = this->pathForSong(songID);

        // Crear un listener dinámico en memoria dinámica
        auto listener = new EventListener<web::WebTask>();

        listener->bind([this, songID, songPath, listener](web::WebTask::Event* event) {
            if (auto res = event->getValue()) {
                if (res->ok()) {
                    auto data = res->data();
                    if (file::writeBinary(songPath, data)) {
                        log::info("Canción {} instalada con éxito.", songID);
                        this->onDownloadSongCompleted(songID);
                    } else {
                        log::error("Error al escribir el archivo de la canción {}.", songID);
                    }
                } else {
                    log::error("Error HTTP {} al consultar el Worker para la canción {}.", res->code(), songID);
                }

                // Limpiar listener al finalizar
                std::erase(g_activeListeners, listener);
                delete listener;
            } 
            else if (event->isCancelled()) {
                log::warn("Petición cancelada para la canción {}.", songID);
                std::erase(g_activeListeners, listener);
                delete listener;
            }
        });

        g_activeListeners.push_back(listener);

        // Iniciar la petición HTTP y enlazar el filtro al listener
        auto task = web::WebRequest().get(workerUrl).send();
        listener->setFilter(task);
    }
};
