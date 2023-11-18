// Retomando la idea del ejercicio Sniper^4 de la guía anterior, tome ese ejercicio
// y modifiquelo para que con el mouse se puedan arrastrar dichos puntos cambiandolos
// de posicion.

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

// Variables 
Texture texture;
Sprite sprites[4];  // Array para almacenar cuatro sprites
bool isDragging[4] = { false, false, false, false };  // Array para controlar si se está arrastrando cada sprite
Vector2f offset[4];  // Array para almacenar la posición inicial del mouse en relación con cada sprite

int main() {

    // Cargamos la textura del archivo
    texture.loadFromFile("rcircle.png");

    // Cargamos el material de cada sprite y los posicionamos en las esquinas
    for (int i = 0; i < 4; ++i) {
        sprites[i].setTexture(texture);
    }

    sprites[0].setPosition(0, 0);                         // Esquina superior izquierda
    sprites[1].setPosition(800 - 128, 0);                 // Esquina superior derecha
    sprites[2].setPosition(0, 600 - 128);                 // Esquina inferior izquierda
    sprites[3].setPosition(800 - 128, 600 - 128);         // Esquina inferior derecha

    sf::RenderWindow ventana(sf::VideoMode(800, 600, 32), "Movimiento de Sprites con SFML");

    while (ventana.isOpen()) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                ventana.close();
            }

            // Detectar eventos de ratón para el movimiento
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    // Verificar si el mouse hizo clic en alguno de los sprites
                    for (int i = 0; i < 4; ++i) {
                        if (sprites[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            isDragging[i] = true;
                            offset[i] = sprites[i].getPosition() - Vector2f(event.mouseButton.x, event.mouseButton.y);
                        }
                    }
                }
            }
            else if (event.type == Event::MouseButtonReleased) {
                if (event.mouseButton.button == Mouse::Left) {
                    // Detener el arrastre de todos los sprites
                    for (int i = 0; i < 4; ++i) {
                        isDragging[i] = false;
                    }
                }
            }
        }

        // Actualizar la posición de los sprites si se están arrastrando
        for (int i = 0; i < 4; ++i) {
            if (isDragging[i]) {
                sprites[i].setPosition(Vector2f(Mouse::getPosition(ventana)) + offset[i]);
            }
        }

        // Limpiar la ventana
        ventana.clear();

        // Dibujar los cuatro sprites
        for (int i = 0; i < 4; ++i) {
            ventana.draw(sprites[i]);
        }

        ventana.display(); // Mostrar todo en la ventana
    }

    return 0;
}
