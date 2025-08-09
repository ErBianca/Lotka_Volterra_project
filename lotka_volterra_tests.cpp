#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "lotka_volterra.hpp"

TEST_CASE(
    "Testing the simulation given the first set of parameters and initial "
    "values") {
  // setting the parameters and the initial values
  pf::Simulation sim1;
  sim1.setValueA(1.1);
  sim1.setValueB(0.4);
  sim1.setValueC(0.1);
  sim1.setValueD(0.4);

  sim1.setx_0(80);
  sim1.sety_0(20);

  sim1.initializeVectors();

  // doing tests divided in subcases
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
    " Testing the simulation given the second set of parameters and initial "
    "values") {
  // changing the values of the parameters and redoing the tests
  // setting the parameters and the initial values
  pf::Simulation sim2;
  sim2.setValueA(1.2);
  sim2.setValueB(0.5);
  sim2.setValueC(0.2);
  sim2.setValueD(0.7);

  sim2.setx_0(25);
  sim2.sety_0(15);

  sim2.initializeVectors();

  // doing tests divided in subcases
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
    "testing the case in which the specie of preys goes extinct (followed by "
    "the predator specie) after a sufficient long time") {
  pf::Simulation sim3;
  sim3.setValueA(0.6);
  sim3.setValueB(2.5);
  sim3.setValueC(0.3);
  sim3.setValueD(0.5);

  sim3.setx_0(8);
  sim3.sety_0(12);

  sim3.initializeVectors();

  sim3.runSimulation(80000);
  CHECK(sim3.getx()[80000] == 0);
  CHECK(sim3.gety()[80000] == 0);
}

TEST_CASE(
    "testing the case in which the species of predators goes extinct and the "
    "number of preys increases indefinitely after a sufficient long time") {
  pf::Simulation sim4;
  sim4.setValueA(3.0);
  sim4.setValueB(0.005);
  sim4.setValueC(0.0001);
  sim4.setValueD(2.5);

  sim4.setx_0(60);
  sim4.sety_0(5);

  sim4.initializeVectors();

  sim4.runSimulation(80000);
  CHECK(sim4.gety()[80000] == 0);
}

// testing equilibrium points
TEST_CASE("Testing equilibrium") {
  pf::Simulation sim5;
  sim5.setValueA(2.0);
  sim5.setValueB(0.01);
  sim5.setValueC(0.02);
  sim5.setValueD(1.5);

  // testing the case in which there aren't any preys or predators
  sim5.setx_0(0);
  sim5.sety_0(0);
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
    pf::Simulation sim6;
    sim6.setValueA(1.1);
    sim6.setValueB(0.4);
    sim6.setValueC(0.1);
    sim6.setValueD(0.4);

    sim6.setx_0(80);
    sim6.sety_0(20);
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
        CHECK(sim6.getx()[1] == doctest::Approx( /* valore atteso */ ));
        CHECK(sim6.gety()[1] == doctest::Approx( /* valore atteso */ ));
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
    pf::Simulation sim7;
    sim7.setValueA(0.6);
    sim7.setValueB(2.5);
    sim7.setValueC(0.3);
    sim7.setValueD(0.5);

    sim7.setx_0(8);
    sim7.sety_0(12);
    sim7.initializeVectors();

    for (int i = 0; i < 80000; ++i)
        sim7.evolveRK4();

    CHECK(sim7.getx().back() <= 1e-6);
    CHECK(sim7.gety().back() <= 1e-6);
}

TEST_CASE("Testing evolveRK4 predator extinction") {
    pf::Simulation sim8;
    sim8.setValueA(3.0);
    sim8.setValueB(0.005);
    sim8.setValueC(0.0001);
    sim8.setValueD(2.5);

    sim8.setx_0(60);
    sim8.sety_0(5);
    sim8.initializeVectors();

    for (int i = 0; i < 80000; ++i)
        sim8.evolveRK4();

    CHECK(sim8.gety().back() <= 1e-6);
    CHECK(sim8.getx().back() > 0); // prede sopravvivono
}
