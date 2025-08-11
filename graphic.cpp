#include "graphic.hpp"

namespace pf {

// Funzione helper per etichette brevi (max 3 caratteri, ma la notazione scientifica non viene troncata)
std::string shortLabel(double val) {
    std::ostringstream oss;
    bool scientificMode = false;

    // Se il valore è molto grande o molto piccolo, usa scientifica
    if (std::abs(val) >= 1000 || (std::abs(val) < 0.01 && val != 0.0)) {
        oss << std::scientific << std::setprecision(0) << val;
        scientificMode = true;
    } else {
        // Calcola quanti decimali mantenere per stare entro 3 caratteri
        if (std::abs(val) >= 100) {
            oss << std::fixed << std::setprecision(0) << val; // es: 100
        } else if (std::abs(val) >= 10) {
            oss << std::fixed << std::setprecision(1) << val; // es: 10.5
        } else {
            oss << std::fixed << std::setprecision(2) << val; // es: 9.99
        }
    }

    std::string s = oss.str();
    if (!scientificMode && s.size() > 3) {
        // Se non siamo in modalità scientifica e ancora troppo lungo, tronca
        s = s.substr(0, 3);
    }
    return s;
}

void plotEquilibriumPointGraph(const std::vector<double> &x, const std::vector<double> &y,
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
  int posX = (desktop.width - window.getSize().x) / 2;
  int posY = (desktop.height - window.getSize().y) / 2;
  window.setPosition(sf::Vector2i(posX, posY));

  // Font per etichette
  sf::Font font;
  if (!font.loadFromFile("DejaVuSans.ttf")) {
    std::cerr << "[!] Font non trovato. Inserisci DejaVuSans.ttf nella "
                 "cartella eseguibile.\n";
    return;
  }

  // Normalizzazione
  auto [minX, maxX] = std::minmax_element(x.begin(), x.end());
  auto [minY, maxY] = std::minmax_element(y.begin(), y.end());

  float margin = 50.0f;
  float scaleX = (800.0f - 2 * margin) / (*maxX - *minX);
  float scaleY = (800.0f - 2 * margin) / (*maxY - *minY);

  // Curva
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

  // Etichette assi
  sf::Text labelX("Prede", font, 14);
  labelX.setFillColor(sf::Color::White);
  labelX.setPosition(350, xAxisY + 25);

  sf::Text labelY("Predatori", font, 14);
  labelY.setFillColor(sf::Color::White);
  labelY.setRotation(-90);
  labelY.setPosition(yAxisX - 50, 350);

  // Punto di equilibrio
  double x_eq = D / C;
  double y_eq = A / B;

  float px_eq = margin + (x_eq - *minX) * scaleX;
  float py_eq = 800.0f - (margin + (y_eq - *minY) * scaleY);

  sf::CircleShape eqPoint(5.0f);
  eqPoint.setFillColor(sf::Color::Red);
  eqPoint.setOrigin(5.0f, 5.0f);
  eqPoint.setPosition(px_eq, py_eq);

  sf::Text eqLabel("Equilibrio", font, 12);
  eqLabel.setFillColor(sf::Color::Red);
  eqLabel.setPosition(px_eq + 8, py_eq - 8);

  // Tacche e unità di misura
  sf::VertexArray ticks(sf::Lines);
  std::vector<sf::Text> tickLabels;

  int numTicks = 10; // numero di tacche per asse

  // Asse X
  for (int i = 0; i <= numTicks; ++i) {
    double val = *minX + i * ((*maxX - *minX) / numTicks);
    float px = margin + (val - *minX) * scaleX;

    // Tacca verticale
    ticks.append(sf::Vertex(sf::Vector2f(px, xAxisY - 5), sf::Color::White));
    ticks.append(sf::Vertex(sf::Vector2f(px, xAxisY + 5), sf::Color::White));

    // Etichetta
    sf::Text t(shortLabel(val), font, 12);
    t.setFillColor(sf::Color::White);
    t.setPosition(px - 10, xAxisY + 8);
    tickLabels.push_back(t);
  }
  // Asse Y
  for (int i = 0; i <= numTicks; ++i) {
    double val = *minY + i * ((*maxY - *minY) / numTicks);
    float py = 800.0f - (margin + (val - *minY) * scaleY);

    // Tacca orizzontale
    ticks.append(sf::Vertex(sf::Vector2f(yAxisX - 5, py), sf::Color::White));
    ticks.append(sf::Vertex(sf::Vector2f(yAxisX + 5, py), sf::Color::White));

    // Etichetta
    sf::Text t(shortLabel(val), font, 12);
    t.setFillColor(sf::Color::White);
    t.setPosition(yAxisX - 35, py - 8);
    tickLabels.push_back(t);
  }

  // Ciclo di rendering
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::Black);
    window.draw(axes);
    window.draw(ticks);
    window.draw(curve);
    window.draw(eqPoint);
    window.draw(labelX);
    window.draw(labelY);
    window.draw(eqLabel);

    for (auto &lbl : tickLabels)
      window.draw(lbl);

    window.display();
  }
}


void plotTimeEvolution(const std::vector<double> &t,
                       const std::vector<double> &x,
                       const std::vector<double> &y) {
  if (t.empty() || x.empty() || y.empty()) {
    std::cerr << "[!] Vettori vuoti, impossibile disegnare il grafico.\n";
    return;
  }

  // Finestra
  sf::RenderWindow window(sf::VideoMode(800, 800), "Andamento prede/predatori",
                          sf::Style::Close);
  window.setFramerateLimit(60);

  // Centrare la finestra
  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  int posX = (desktop.width - window.getSize().x) / 2;
  int posY = (desktop.height - window.getSize().y) / 2;
  window.setPosition(sf::Vector2i(posX, posY));

  // Carica font
  sf::Font font;
  if (!font.loadFromFile("DejaVuSans.ttf")) {
    std::cerr << "[!] Font non trovato.\n";
    return;
  }

  // Limiti per normalizzazione
  auto [tMin, tMax] = std::minmax_element(t.begin(), t.end());
  auto [xMin, xMax] = std::minmax_element(x.begin(), x.end());
  auto [yMin, yMax] = std::minmax_element(y.begin(), y.end());

  float leftMargin = 70.f;
  float bottomMargin = 70.f;
  float topMargin = 40.f;
  float rightMargin = 40.f;
  float plotWidth = window.getSize().x - leftMargin - rightMargin;
  float plotHeight = window.getSize().y - topMargin - bottomMargin;

  auto normalize = [&](double val, double minVal, double maxVal,
                       float axisSize) {
    return static_cast<float>((val - minVal) / (maxVal - minVal) * axisSize);
  };

  // Curve
  sf::VertexArray preyCurve(sf::LineStrip, x.size());
  sf::VertexArray predatorCurve(sf::LineStrip, y.size());

  for (size_t i = 0; i < t.size(); ++i) {
    float px = leftMargin + normalize(t[i], *tMin, *tMax, plotWidth);
    float preyY = window.getSize().y - bottomMargin -
                  normalize(x[i], *xMin, *xMax, plotHeight);
    float predY = window.getSize().y - bottomMargin -
                  normalize(y[i], *yMin, *yMax, plotHeight);

    preyCurve[i].position = sf::Vector2f(px, preyY);
    preyCurve[i].color = sf::Color::Green;

    predatorCurve[i].position = sf::Vector2f(px, predY);
    predatorCurve[i].color = sf::Color::Red;
  }

  // Assi
  sf::Vertex xAxis[] = {
      sf::Vertex(sf::Vector2f(leftMargin, window.getSize().y - bottomMargin)),
      sf::Vertex(sf::Vector2f(window.getSize().x - rightMargin,
                              window.getSize().y - bottomMargin))};
  sf::Vertex yAxis[] = {
      sf::Vertex(sf::Vector2f(leftMargin, window.getSize().y - bottomMargin)),
      sf::Vertex(sf::Vector2f(leftMargin, topMargin))};

  for (auto &v : xAxis) v.color = sf::Color::White;
  for (auto &v : yAxis) v.color = sf::Color::White;

  // Etichette assi
  sf::Text labelX("Tempo", font, 14);
  labelX.setFillColor(sf::Color::White);
  labelX.setPosition(window.getSize().x / 2.f - 20.f,
                     window.getSize().y - 40.f);

  sf::Text labelY("Popolazione", font, 14);
  labelY.setFillColor(sf::Color::White);
  labelY.setRotation(-90);
  labelY.setPosition(5.f, window.getSize().y / 2.f + 20.f); // spostata per non sovrapporsi

  // Tacche e unità di misura
  sf::VertexArray ticks(sf::Lines);
  std::vector<sf::Text> tickLabels;
  int numTicks = 10;

  // Tacche asse X
  for (int i = 0; i <= numTicks; ++i) {
    double val = *tMin + i * ((*tMax - *tMin) / numTicks);
    float px = leftMargin + normalize(val, *tMin, *tMax, plotWidth);

    ticks.append(sf::Vertex(sf::Vector2f(px, window.getSize().y - bottomMargin - 5), sf::Color::White));
    ticks.append(sf::Vertex(sf::Vector2f(px, window.getSize().y - bottomMargin + 5), sf::Color::White));

    sf::Text tLabel(shortLabel(val), font, 12);
    tLabel.setFillColor(sf::Color::White);
    tLabel.setPosition(px - 10, window.getSize().y - bottomMargin + 8);
    tickLabels.push_back(tLabel);
  }

  // Tacche asse Y (in base alla popolazione massima tra x e y)
  double yMinTotal = std::min(*xMin, *yMin);
  double yMaxTotal = std::max(*xMax, *yMax);

  for (int i = 0; i <= numTicks; ++i) {
    double val = yMinTotal + i * ((yMaxTotal - yMinTotal) / numTicks);
    float py = window.getSize().y - bottomMargin - normalize(val, yMinTotal, yMaxTotal, plotHeight);

    ticks.append(sf::Vertex(sf::Vector2f(leftMargin - 5, py), sf::Color::White));
    ticks.append(sf::Vertex(sf::Vector2f(leftMargin + 5, py), sf::Color::White));

    sf::Text yLabel(shortLabel(val), font, 12);
    yLabel.setFillColor(sf::Color::White);
    yLabel.setPosition(leftMargin - 45, py - 8); // posizionata per non toccare labelY
    tickLabels.push_back(yLabel);
  }

  // Legenda
  sf::RectangleShape greenBox(sf::Vector2f(10.f, 10.f));
  greenBox.setPosition(720.f, 10.f);
  greenBox.setFillColor(sf::Color::Green);

  sf::Text labelPrede("Prede", font, 13);
  labelPrede.setFillColor(sf::Color::White);
  labelPrede.setPosition(735.f, 7.f);

  sf::RectangleShape redBox(sf::Vector2f(10.f, 10.f));
  redBox.setPosition(720.f, 30.f);
  redBox.setFillColor(sf::Color::Red);

  sf::Text labelPredatori("Predatori", font, 13);
  labelPredatori.setFillColor(sf::Color::White);
  labelPredatori.setPosition(735.f, 27.f);

  // Rendering
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::Black);
    window.draw(preyCurve);
    window.draw(predatorCurve);
    window.draw(xAxis, 2, sf::Lines);
    window.draw(yAxis, 2, sf::Lines);
    window.draw(ticks);
    for (auto &lbl : tickLabels) window.draw(lbl);
    window.draw(labelX);
    window.draw(labelY);
    window.draw(greenBox);
    window.draw(labelPrede);
    window.draw(redBox);
    window.draw(labelPredatori);
    window.display();
  }
}

} // namespace pf
