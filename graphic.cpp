#include "graphic.hpp"

namespace pf {

// Funzione helper per etichette brevi (max 3 caratteri, ma la notazione
// scientifica non viene troncata)
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

// Funzione per disegnare il grafico del punto di equilibrio
void plotEquilibriumPointGraph(const std::vector<double> &x,
                               const std::vector<double> &y, double A, double B,
                               double C, double D) {
  if (x.empty() || y.empty()) {
    std::cerr << "[!] Vettori vuoti, impossibile disegnare la figura intorno "
                 "al punto di equilibrio.\n";
    return;
  }

  // Creazione finestra
  sf::RenderWindow window(sf::VideoMode(800, 800),
                          "Figura intorno al punto di equilibrio",
                          sf::Style::Close);
  window.setFramerateLimit(60);

  // Centrare la finestra
  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  int posX = static_cast<int>((desktop.width - window.getSize().x) / 2);
  int posY = static_cast<int>((desktop.height - window.getSize().y) / 2);
  window.setPosition(sf::Vector2i(posX, posY));

  // Caricamento font per etichette
  sf::Font font;
  if (!font.loadFromFile("DejaVuSans.ttf")) {
    std::cerr << "[!] Font non trovato. Inserisci DejaVuSans.ttf nella "
                 "cartella eseguibile.\n";
    return;
  }

  // Trova valori minimi e massimi per normalizzazione
  auto [minXIt, maxXIt] = std::minmax_element(x.begin(), x.end());
  auto [minYIt, maxYIt] = std::minmax_element(y.begin(), y.end());
  double minX = *minXIt, maxX = *maxXIt;
  double minY = *minYIt, maxY = *maxYIt;

  float margin = 50.0f; // margine della finestra
  float scaleX = static_cast<float>((800.0 - 2.0 * margin) / (maxX - minX));
  float scaleY = static_cast<float>((800.0 - 2.0 * margin) / (maxY - minY));

  // Creazione curva
  sf::VertexArray curve(sf::LineStrip, x.size());
  for (size_t i = 0; i < x.size(); ++i) {
    float px = margin + static_cast<float>(x[i] - minX) * scaleX;
    float py = 800.0f - (margin + static_cast<float>(y[i] - minY) * scaleY);
    curve[i].position = sf::Vector2f(px, py);
    curve[i].color = sf::Color::Cyan;
  }

  // Assi cartesiani
  sf::VertexArray axes(sf::Lines, 4);
  float xAxisY = 800.0f - (margin + static_cast<float>(0.0 - minY) * scaleY);
  float yAxisX = margin + static_cast<float>(0.0 - minX) * scaleX;

  // Asse X
  axes[0].position = sf::Vector2f(margin, xAxisY);
  axes[1].position = sf::Vector2f(800.0f - margin, xAxisY);

  // Asse Y
  axes[2].position = sf::Vector2f(yAxisX, margin);
  axes[3].position = sf::Vector2f(yAxisX, 800.0f - margin);

  // Colore assi
  for (std::size_t i = 0; i < axes.getVertexCount(); ++i)
    axes[i].color = sf::Color::White;

  // Etichette assi
  sf::Text labelX("Prede", font, 14);
  labelX.setFillColor(sf::Color::White);
  labelX.setPosition(350.0f, xAxisY + 25.0f);

  sf::Text labelY("Predatori", font, 14);
  labelY.setFillColor(sf::Color::White);
  labelY.setRotation(-90.0f);
  labelY.setPosition(yAxisX - 50.0f, 350.0f);

  // Punto di equilibrio
  double x_eq = D / C;
  double y_eq = A / B;
  float px_eq = margin + static_cast<float>(x_eq - minX) * scaleX;
  float py_eq = 800.0f - (margin + static_cast<float>(y_eq - minY) * scaleY);

  sf::CircleShape eqPoint(5.0f);
  eqPoint.setFillColor(sf::Color::Red);
  eqPoint.setOrigin(5.0f, 5.0f);
  eqPoint.setPosition(px_eq, py_eq);

  sf::Text eqLabel("Equilibrio", font, 12);
  eqLabel.setFillColor(sf::Color::Red);
  eqLabel.setPosition(px_eq + 8.0f, py_eq - 8.0f);

  // Tacche e unità di misura
  sf::VertexArray ticks(sf::Lines);
  std::vector<sf::Text> tickLabels;
  int numTicks = 10; // numero di tacche per asse

  // Tacche asse X
  for (int i = 0; i <= numTicks; ++i) {
    double valX = minX + i * ((maxX - minX) / numTicks);
    float px = margin + static_cast<float>(valX - minX) * scaleX;

    // Tacca verticale
    ticks.append(sf::Vertex(sf::Vector2f(px, xAxisY - 5.0f), sf::Color::White));
    ticks.append(sf::Vertex(sf::Vector2f(px, xAxisY + 5.0f), sf::Color::White));

    // Etichetta
    sf::Text t(shortLabel(valX), font, 12);
    t.setFillColor(sf::Color::White);
    t.setPosition(px - 10.0f, xAxisY + 8.0f);
    tickLabels.push_back(t);
  }

  // Tacche asse Y
  for (int i = 0; i <= numTicks; ++i) {
    double valY = minY + i * ((maxY - minY) / numTicks);
    float py = 800.0f - (margin + static_cast<float>(valY - minY) * scaleY);

    // Tacca orizzontale
    ticks.append(sf::Vertex(sf::Vector2f(yAxisX - 5.0f, py), sf::Color::White));
    ticks.append(sf::Vertex(sf::Vector2f(yAxisX + 5.0f, py), sf::Color::White));

    // Etichetta
    sf::Text t(shortLabel(valY), font, 12);
    t.setFillColor(sf::Color::White);
    t.setPosition(yAxisX - 35.0f, py - 8.0f);
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

// Funzione per disegnare l’andamento temporale di prede e predatori
void plotTimeEvolution(const std::vector<double> &t,
                       const std::vector<double> &x,
                       const std::vector<double> &y) {
  if (t.empty() || x.empty() || y.empty()) {
    std::cerr << "[!] Vettori vuoti, impossibile disegnare il grafico.\n";
    return;
  }

  // Creazione finestra
  sf::RenderWindow window(sf::VideoMode(800, 800), "Andamento prede/predatori",
                          sf::Style::Close);
  window.setFramerateLimit(60);

  // Centrare la finestra
  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  int posX = static_cast<int>((desktop.width - window.getSize().x) / 2);
  int posY = static_cast<int>((desktop.height - window.getSize().y) / 2);
  window.setPosition(sf::Vector2i(posX, posY));

  // Caricamento font
  sf::Font font;
  if (!font.loadFromFile("DejaVuSans.ttf")) {
    std::cerr << "[!] Font non trovato.\n";
    return;
  }

  // Limiti per normalizzazione
  auto [tMinIt, tMaxIt] = std::minmax_element(t.begin(), t.end());
  auto [xMinIt, xMaxIt] = std::minmax_element(x.begin(), x.end());
  auto [yMinIt, yMaxIt] = std::minmax_element(y.begin(), y.end());
  double tMin = *tMinIt, tMax = *tMaxIt;
  double xMin = *xMinIt, xMax = *xMaxIt;
  double yMin = *yMinIt, yMax = *yMaxIt;

  float leftMargin = 70.0f;
  float bottomMargin = 70.0f;
  float topMargin = 40.0f;
  float rightMargin = 40.0f;
  float plotWidth =
      static_cast<float>(window.getSize().x) - leftMargin - rightMargin;
  float plotHeight =
      static_cast<float>(window.getSize().y) - topMargin - bottomMargin;

  // Funzione lambda per normalizzare un valore
  auto normalize = [&](double val, double minVal, double maxVal,
                       float axisSize) {
    return static_cast<float>((val - minVal) / (maxVal - minVal) * axisSize);
  };

  // Curve
  sf::VertexArray preyCurve(sf::LineStrip, x.size());
  sf::VertexArray predatorCurve(sf::LineStrip, y.size());

  for (size_t i = 0; i < t.size(); ++i) {
    float px = leftMargin + normalize(t[i], tMin, tMax, plotWidth);
    float preyY = static_cast<float>(window.getSize().y) - bottomMargin -
                  normalize(x[i], xMin, xMax, plotHeight);
    float predY = static_cast<float>(window.getSize().y) - bottomMargin -
                  normalize(y[i], yMin, yMax, plotHeight);

    preyCurve[i].position = sf::Vector2f(px, preyY);
    preyCurve[i].color = sf::Color::Green;

    predatorCurve[i].position = sf::Vector2f(px, predY);
    predatorCurve[i].color = sf::Color::Red;
  }

  // Assi
  sf::Vertex xAxis[] = {
      sf::Vertex(sf::Vector2f(
          leftMargin, static_cast<float>(window.getSize().y) - bottomMargin)),
      sf::Vertex(
          sf::Vector2f(static_cast<float>(window.getSize().x) - rightMargin,
                       static_cast<float>(window.getSize().y) - bottomMargin))};
  sf::Vertex yAxis[] = {
      sf::Vertex(sf::Vector2f(
          leftMargin, static_cast<float>(window.getSize().y) - bottomMargin)),
      sf::Vertex(sf::Vector2f(leftMargin, topMargin))};

  for (auto &v : xAxis)
    v.color = sf::Color::White;
  for (auto &v : yAxis)
    v.color = sf::Color::White;

  // Etichette assi
  sf::Text labelX("Tempo", font, 14);
  labelX.setFillColor(sf::Color::White);
  labelX.setPosition(static_cast<float>(window.getSize().x) / 2.0f - 20.0f,
                     static_cast<float>(window.getSize().y) - 40.0f);

  sf::Text labelY("Popolazione", font, 14);
  labelY.setFillColor(sf::Color::White);
  labelY.setRotation(-90.0f);
  labelY.setPosition(5.0f, static_cast<float>(window.getSize().y) / 2.0f +
                               20.0f); // spostata per non sovrapporsi

  // Tacche e unità di misura
  sf::VertexArray ticks(sf::Lines);
  std::vector<sf::Text> tickLabels;
  int numTicks = 10;

  // Tacche asse X
  for (int i = 0; i <= numTicks; ++i) {
    double val = tMin + i * ((tMax - tMin) / numTicks);
    float px = leftMargin + normalize(val, tMin, tMax, plotWidth);

    // Tacca verticale
    ticks.append(
        sf::Vertex(sf::Vector2f(px, static_cast<float>(window.getSize().y) -
                                        bottomMargin - 5.0f),
                   sf::Color::White));
    ticks.append(
        sf::Vertex(sf::Vector2f(px, static_cast<float>(window.getSize().y) -
                                        bottomMargin + 5.0f),
                   sf::Color::White));

    // Etichetta
    sf::Text tLabel(shortLabel(val), font, 12);
    tLabel.setFillColor(sf::Color::White);
    tLabel.setPosition(px - 10.0f, static_cast<float>(window.getSize().y) -
                                       bottomMargin + 8.0f);
    tickLabels.push_back(tLabel);
  }

  // Tacche asse Y (basata sulla popolazione massima tra x e y)
  double yMinTotal = std::min(xMin, yMin);
  double yMaxTotal = std::max(xMax, yMax);

  for (int i = 0; i <= numTicks; ++i) {
    double val = yMinTotal + i * ((yMaxTotal - yMinTotal) / numTicks);
    float py = static_cast<float>(window.getSize().y) - bottomMargin -
               normalize(val, yMinTotal, yMaxTotal, plotHeight);

    // Tacca orizzontale
    ticks.append(
        sf::Vertex(sf::Vector2f(leftMargin - 5.0f, py), sf::Color::White));
    ticks.append(
        sf::Vertex(sf::Vector2f(leftMargin + 5.0f, py), sf::Color::White));

    // Etichetta
    sf::Text yLabelTick(shortLabel(val), font, 12);
    yLabelTick.setFillColor(sf::Color::White);
    yLabelTick.setPosition(leftMargin - 45.0f,
                           py - 8.0f); // posizionata per non toccare labelY
    tickLabels.push_back(yLabelTick);
  }

  // Legenda
  sf::RectangleShape greenBox(sf::Vector2f(10.0f, 10.0f));
  greenBox.setPosition(720.0f, 10.0f);
  greenBox.setFillColor(sf::Color::Green);

  sf::Text labelPrede("Prede", font, 13);
  labelPrede.setFillColor(sf::Color::White);
  labelPrede.setPosition(735.0f, 7.0f);

  sf::RectangleShape redBox(sf::Vector2f(10.0f, 10.0f));
  redBox.setPosition(720.0f, 30.0f);
  redBox.setFillColor(sf::Color::Red);

  sf::Text labelPredatori("Predatori", font, 13);
  labelPredatori.setFillColor(sf::Color::White);
  labelPredatori.setPosition(735.0f, 27.0f);

  // Ciclo di rendering
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
    for (auto &lbl : tickLabels)
      window.draw(lbl);
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
