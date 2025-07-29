#include "graphic.hpp"


void pf::plotLissajous(const std::vector<double>& x, const std::vector<double>& y) {
    if (x.empty() || y.empty()) {
        std::cerr << "[!] Vettori vuoti, impossibile disegnare la figura di Lissajous.\n";
        return;
    }

    // Finestra
    sf::RenderWindow window(sf::VideoMode(800, 800), "Figura di Lissajous", sf::Style::Close);
    window.setFramerateLimit(60);

    // Normalizza i dati
    auto [minX, maxX] = std::minmax_element(x.begin(), x.end());
    auto [minY, maxY] = std::minmax_element(y.begin(), y.end());

    float scaleX = 700.0f / (*maxX - *minX);
    float scaleY = 700.0f / (*maxY - *minY);

    sf::VertexArray curve(sf::LineStrip, x.size());

    for (size_t i = 0; i < x.size(); ++i) {
        float px = 50.0f + (x[i] - *minX) * scaleX;
        float py = 750.0f - (y[i] - *minY) * scaleY;
        curve[i].position = sf::Vector2f(px, py);
        curve[i].color = sf::Color::Cyan;
    }

    // Loop di rendering
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(curve);
        window.display();
    }
}