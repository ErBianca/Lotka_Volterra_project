#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "lotka_volterra.hpp"
#include <cmath>

TEST_CASE(
    "Testing the simulation given the first set of parameters and initial values") {

  pf::Simulation sim1(1.1, 0.4, 0.1, 0.4, 80, 20, 0.001);
  sim1.initializeVectors();

  SUBCASE("testing the values of e2_x and e2_y") {
    CHECK(sim1.e2_x() == 4);
    CHECK(sim1.e2_y() == 2.75);
  }

  SUBCASE("testing the initial values of x,y and H") {
    CHECK(sim1.getx()[0] == 80);
    CHECK(sim1.gety()[0] == 20);
    CHECK(sim1.getH()[0] == doctest::Approx(10.95188));
  }

  SUBCASE("testing the values of x,y and H after 0.001") {
    sim1.runSimulation(1);
    CHECK(sim1.getx()[1] == doctest::Approx(79.855));
    CHECK(sim1.gety()[1] == doctest::Approx(20.032));
    CHECK(sim1.getH()[1] == doctest::Approx(10.94915));

    CHECK(sim1.getx().size() == 2);
    CHECK(sim1.gety().size() == 2);
    CHECK(sim1.getH().size() == 2);
    CHECK(sim1.gett().size() == 2);
  }

  SUBCASE("testing the values of x,y and H after 0.003") {
    sim1.runSimulation(3);
    CHECK(sim1.getx()[3] == doctest::Approx(79.56548));
    CHECK(sim1.gety()[3] == doctest::Approx(20.09587));
    CHECK(sim1.getH()[3] == doctest::Approx(10.94370));

    CHECK(sim1.getx().size() == 4);
    CHECK(sim1.gety().size() == 4);
    CHECK(sim1.getH().size() == 4);
    CHECK(sim1.gett().size() == 4);
  }

  SUBCASE("testing the dimension of the vectors after 0.010") {
    sim1.runSimulation(10);
    CHECK(sim1.getx().size() == 11);
    CHECK(sim1.gety().size() == 11);
    CHECK(sim1.getH().size() == 11);
    CHECK(sim1.gett().size() == 11);
  }

  SUBCASE("testing the values of x,y and H after 0.05") {
    sim1.runSimulation(50);
    CHECK(sim1.getx()[50] == doctest::Approx(72.6642115121));
    CHECK(sim1.gety()[50] == doctest::Approx(21.5677566003));
    CHECK(sim1.getH()[50] == doctest::Approx(10.8008648021));

    CHECK(sim1.getx().size() == 51);
    CHECK(sim1.gety().size() == 51);
    CHECK(sim1.getH().size() == 51);
    CHECK(sim1.gett().size() == 51);
  }

  SUBCASE("testing the values of x,y and H after 0.37") {
    sim1.runSimulation(370);
    CHECK(sim1.getx()[370] == doctest::Approx(31.4399027195));
    CHECK(sim1.gety()[370] == doctest::Approx(28.4470110688));
    CHECK(sim1.getH()[370] == doctest::Approx(9.4607161445));

    CHECK(sim1.getx().size() == 371);
    CHECK(sim1.gety().size() == 371);
    CHECK(sim1.getH().size() == 371);
    CHECK(sim1.gett().size() == 371);
  }
}

TEST_CASE(
    "Testing the simulation given the second set of parameters and initial values") {

  pf::Simulation sim2(1.2, 0.5, 0.2, 0.7, 25, 15, 0.001);
  sim2.initializeVectors();

  SUBCASE("testing the values of e2_x and e2_y") {
    CHECK(sim2.e2_x() == doctest::Approx(3.5));
    CHECK(sim2.e2_y() == doctest::Approx(2.4));
  }

  SUBCASE("testing the initial values of x, y, and H") {
    CHECK(sim2.getx()[0] == 25);
    CHECK(sim2.gety()[0] == 15);
    CHECK(sim2.getH()[0] == doctest::Approx(6.99713));
  }

  SUBCASE("testing the values of x, y, and H after 0.001") {
    sim2.runSimulation(1);
    CHECK(sim2.getx()[1] == doctest::Approx(24.95189));
    CHECK(sim2.gety()[1] == doctest::Approx(15.01092));
    CHECK(sim2.getH()[1] == doctest::Approx(6.99344));

    CHECK(sim2.getx().size() == 2);
    CHECK(sim2.gety().size() == 2);
    CHECK(sim2.getH().size() == 2);
    CHECK(sim2.gett().size() == 2);
  }

  SUBCASE("testing the values of x, y, and H after 0.003") {
    sim2.runSimulation(3);
    CHECK(sim2.getx()[3] == doctest::Approx(24.85574));
    CHECK(sim2.gety()[3] == doctest::Approx(15.03269));
    CHECK(sim2.getH()[3] == doctest::Approx(6.98606));

    CHECK(sim2.getx().size() == 4);
    CHECK(sim2.gety().size() == 4);
    CHECK(sim2.getH().size() == 4);
    CHECK(sim2.gett().size() == 4);
  }

  SUBCASE("testing the dimension of the vectors after 0.027") {
    sim2.runSimulation(27);
    CHECK(sim2.getx().size() == 28);
    CHECK(sim2.gety().size() == 28);
    CHECK(sim2.getH().size() == 28);
    CHECK(sim2.gett().size() == 28);
  }

  SUBCASE("testing the values of x, y, and H after 0.05") {
    sim2.runSimulation(50);
    CHECK(sim2.getx()[50] == doctest::Approx(22.6435977623));
    CHECK(sim2.gety()[50] == doctest::Approx(15.5047001662));
    CHECK(sim2.getH()[50] == doctest::Approx(6.8077837714));

    CHECK(sim2.getx().size() == 51);
    CHECK(sim2.gety().size() == 51);
    CHECK(sim2.getH().size() == 51);
    CHECK(sim2.gett().size() == 51);
  }

  SUBCASE("testing the values of x, y, and H after 41") {
    sim2.runSimulation(41000);
    CHECK(sim2.getx()[41000] == doctest::Approx(32.3056759334));
    CHECK(sim2.gety()[41000] == doctest::Approx(13.3331269875));
    CHECK(sim2.getH()[41000] == doctest::Approx(7.5867265950));

    CHECK(sim2.getx().size() == 41001);
    CHECK(sim2.gety().size() == 41001);
    CHECK(sim2.getH().size() == 41001);
    CHECK(sim2.gett().size() == 41001);
  }
}

TEST_CASE(
    "testing the case in which the specie of preys goes extinct (followed by the predator specie)") {

  pf::Simulation sim3(0.6, 2.5, 0.3, 0.5, 8, 12, 0.001);
  sim3.initializeVectors();

  sim3.runSimulation(80000);
  CHECK(sim3.getx()[80000] == 0);
  CHECK(sim3.gety()[80000] == 0);
}

TEST_CASE(
    "testing the case in which predators go extinct and preys increase indefinitely") {

  pf::Simulation sim4(3.0, 0.005, 0.0001, 2.5, 60, 5, 0.001);
  sim4.initializeVectors();

  sim4.runSimulation(80000);
  CHECK(sim4.gety()[80000] == 0);
}

TEST_CASE("Testing equilibrium") {
  pf::Simulation sim5(2.0, 0.01, 0.02, 1.5, 0, 0, 0.001);
  sim5.initializeVectors();

  sim5.runSimulation(80000);
  CHECK(sim5.getx()[70000] == 0);
  CHECK(sim5.gety()[65000] == 0);
  CHECK(sim5.getx()[700] == 0);
  CHECK(sim5.gety()[3456] == 0);
  CHECK(sim5.getx()[12360] == 0);
  CHECK(sim5.gety()[5000] == 0);
}

TEST_CASE("Testing evolveRK4 with first parameter set") {
    pf::Simulation sim6(1.1, 0.4, 0.1, 0.4, 80, 20, 0.001);
    sim6.initializeVectors();

    SUBCASE("Initial state") {
        CHECK(sim6.getx()[0] == doctest::Approx(80));
        CHECK(sim6.gety()[0] == doctest::Approx(20));
        CHECK(sim6.getH()[0] == doctest::Approx(
            -0.4 * std::log(80) + 0.1 * 80 + 0.4 * 20 - 1.1 * std::log(20)
        ));
    }

    SUBCASE("After one RK4 step") {
        sim6.evolveRK4();
        CHECK(sim6.getx()[1] == doctest::Approx(79.447485));
        CHECK(sim6.gety()[1] == doctest::Approx(20.152023));
        CHECK(sim6.getH()[1] == doctest::Approx(
            -0.4 * std::log(sim6.getx()[1]) + 0.1 * sim6.getx()[1] +
             0.4 * sim6.gety()[1] - 1.1 * std::log(sim6.gety()[1])
        ));
        CHECK(sim6.getx().size() == 2);
        CHECK(sim6.gety().size() == 2);
        CHECK(sim6.getH().size() == 2);
    }

    SUBCASE("After 10 RK4 steps") {
        for (int i = 0; i < 10; ++i)
            sim6.evolveRK4();
        CHECK(sim6.getx().size() == 11);
        CHECK(sim6.gety().size() == 11);
        CHECK(sim6.getH().size() == 11);
    }
}

TEST_CASE("Testing evolveRK4 extinction scenario") {
    pf::Simulation sim7(0.6, 2.5, 0.3, 0.5, 8, 12, 0.001);
    sim7.initializeVectors();

    for (int i = 0; i < 80000; ++i)
        sim7.evolveRK4();

    CHECK(sim7.getx().back() <= 1e-6);
    CHECK(sim7.gety().back() <= 1e-6);
}

TEST_CASE("Testing evolveRK4 predator extinction") {
    pf::Simulation sim8(3.0, 0.005, 0.0001, 2.5, 60, 5, 0.001);
    sim8.initializeVectors();

    for (int i = 0; i < 80000; ++i)
        sim8.evolveRK4();

    CHECK(sim8.gety().back() <= 1e-6);
    CHECK(sim8.getx().back() > 0); // prede sopravvivono
}
