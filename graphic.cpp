#include "graphic.hpp"

namespace pf {
void plotLissajous(const std::vector<double> &x, const std::vector<double> &y,
                   double A, double B, double C, double D) {
  if (x.empty() || y.empty()) {
    std::cerr
        << "[!] Vettori vuoti, impossibile disegnare la figura di Lissajous.\n";
    return;
  }

  // Finestra
  sf::RenderWindow window(sf::VideoMode(800, 800), "Figura di Lissajous",
                          sf::Style::Close);
  window.setFramerateLimit(60);

  // Centrare la finestra
  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  unsigned int screenWidth = desktop.width;
  unsigned int screenHeight = desktop.height;

  int posX = (screenWidth - window.getSize().x) / 2;
  int posY = (screenHeight - window.getSize().y) / 2;
  window.setPosition(sf::Vector2i(posX, posY));

  // Font per etichette
  sf::Font font;
  if (!font.loadFromFile("DejaVuSans.ttf")) {
    std::cerr << "[!] Font non trovato. Inserisci arial.ttf nella cartella "
                 "eseguibile.\n";
    return;
  }

  // Normalizzazione
  auto [minX, maxX] = std::minmax_element(x.begin(), x.end());
  auto [minY, maxY] = std::minmax_element(y.begin(), y.end());

  float margin = 50.0f;
  float scaleX = (800.0f - 2 * margin) / (*maxX - *minX);
  float scaleY = (800.0f - 2 * margin) / (*maxY - *minY);

  // Costruisci curva
  sf::VertexArray curve(sf::LineStrip, x.size());
  for (size_t i = 0; i < x.size(); ++i) {
    float px = margin + (x[i] - *minX) * scaleX;
    float py = 800.0f - (margin + (y[i] - *minY) * scaleY);
    curve[i].position = sf::Vector2f(px, py);
    curve[i].color = sf::Color::Cyan;
  }

  // Assi cartesiani
  sf::VertexArray axes(sf::Lines, 4);
  float xAxisY = 800.0f - (margin + (0 - *minY) * scaleY);
  float yAxisX = margin + (0 - *minX) * scaleX;

  // Asse X
  axes[0].position = sf::Vector2f(margin, xAxisY);
  axes[1].position = sf::Vector2f(800.0f - margin, xAxisY);

  // Asse Y
  axes[2].position = sf::Vector2f(yAxisX, margin);
  axes[3].position = sf::Vector2f(yAxisX, 800.0f - margin);

  for (int i = 0; i < 4; ++i)
    axes[i].color = sf::Color::White;

  // Etichette
  sf::Text labelX("Prede", font, 14);
  labelX.setFillColor(sf::Color::White);
  labelX.setPosition(720, xAxisY + 5);

  sf::Text labelY("Predatori", font, 14);
  labelY.setFillColor(sf::Color::White);
  labelY.setRotation(-90);
  labelY.setPosition(yAxisX - 30, 400.);

  // Punto di equilibrio (D/C, A/B)
  double x_eq = D / C;
  double y_eq = A / B;

  float px_eq = margin + (x_eq - *minX) * scaleX;
  float py_eq = 800.0f - (margin + (y_eq - *minY) * scaleY);

  sf::CircleShape eqPoint(5.0f);
  eqPoint.setFillColor(sf::Color::Red);
  eqPoint.setOrigin(5.0f, 5.0f);
  eqPoint.setPosition(px_eq, py_eq);

  // Etichetta del punto di equilibrio
  sf::Text eqLabel("Equilibrio", font, 12);
  eqLabel.setFillColor(sf::Color::Red);
  eqLabel.setPosition(px_eq + 8, py_eq - 8);

  // Ciclo di rendering
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::Black);
    window.draw(axes);
    window.draw(curve);
    window.draw(eqPoint);
    window.draw(labelX);
    window.draw(labelY);
    window.draw(eqLabel);
    window.display();
  }
}
} // namespace pf
