# Lotka-Volterra Project

Implementazione in **C++** del modello matematico preda-predatore di Lotka-Volterra, con simulazioni grafiche e test automatizzati.

## 📌 Caratteristiche
- Simulazione numerica delle dinamiche preda-predatore.
- Visualizzazione grafica dell’evoluzione temporale.
- Suite di test automatizzati basati su `doctest.h`.
- Struttura modulare del codice (separazione tra modello, grafica e test).

## 🔧 Requisiti
- Compilatore **C++11** (o superiore).
- **CMake** per la gestione della build.
- [doctest](https://github.com/doctest/doctest) (header-only, incluso nel progetto).
- Libreria grafica **SFML** necessaria per la parte grafica

## 🚀 Installazione e utilizzo
Clona la repository ed esegui la build con CMake:

```bash
git clone https://github.com/ErBianca/Lotka_Volterra_project.git
cd Lotka_Volterra_project
mkdir build && cd build
cmake ..
make
./Lotka_Volterra       # esegue la simulazione

