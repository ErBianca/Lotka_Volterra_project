#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "lotka_volterra.hpp"

TEST_CASE(
    "Testing the simulation given the first set of parameters and initial "
    "values") {
  // setting the parameters and the initial values
  pf::Simulation simulation1;
  simulation1.setValueA(1.1);
  simulation1.setValueB(0.4);
  simulation1.setValueC(0.1);
  simulation1.setValueD(0.4);

  simulation1.setx_0(80);
  simulation1.sety_0(20);

  simulation1.initializeVectors();

  // doing tests divided in subcases
  SUBCASE("testing the values of e2_x and e2_y") {
    CHECK(simulation1.e2_x() == 4);
    CHECK(simulation1.e2_y() == 2.75);
  }

  SUBCASE("testing the initial values of x,y and H") {
    CHECK(simulation1.getx()[0] == 80);
    CHECK(simulation1.gety()[0] == 20);
    CHECK(simulation1.getH()[0] == doctest::Approx(10.95188));
  }

  SUBCASE("testing the values of x,y and H after 0.001") {
    simulation1.runSimulation(1);
    CHECK(simulation1.getx()[1] == doctest::Approx(79.855));
    CHECK(simulation1.gety()[1] == doctest::Approx(20.032));
    CHECK(simulation1.getH()[1] == doctest::Approx(10.94915));

    CHECK(simulation1.getx().size() == 2);
    CHECK(simulation1.gety().size() == 2);
    CHECK(simulation1.getH().size() == 2);
    CHECK(simulation1.gett().size() == 2);
  }

  SUBCASE("testing the values of x,y and H after 0.003") {
    simulation1.runSimulation(3);
    CHECK(simulation1.getx()[3] == doctest::Approx(79.56548));
    CHECK(simulation1.gety()[3] == doctest::Approx(20.09587));
    CHECK(simulation1.getH()[3] == doctest::Approx(10.94370));

    CHECK(simulation1.getx().size() == 4);
    CHECK(simulation1.gety().size() == 4);
    CHECK(simulation1.getH().size() == 4);
    CHECK(simulation1.gett().size() == 4);
  }

  SUBCASE("testing the dimension of the vectors after 0.010") {
    simulation1.runSimulation(10);
    CHECK(simulation1.getx().size() == 11);
    CHECK(simulation1.gety().size() == 11);
    CHECK(simulation1.getH().size() == 11);
    CHECK(simulation1.gett().size() == 11);
  }

  SUBCASE("testing the values of x,y and H after 0.05") {
    simulation1.runSimulation(50);
    CHECK(simulation1.getx()[50] == doctest::Approx(72.6642115121));
    CHECK(simulation1.gety()[50] == doctest::Approx(21.5677566003));
    CHECK(simulation1.getH()[50] == doctest::Approx(10.8008648021));

    CHECK(simulation1.getx().size() == 51);
    CHECK(simulation1.gety().size() == 51);
    CHECK(simulation1.getH().size() == 51);
    CHECK(simulation1.gett().size() == 51);
  }
  SUBCASE("testing the values of x,y and H after 0.37") {
    simulation1.runSimulation(370);
    CHECK(simulation1.getx()[370] == doctest::Approx(31.4399027195));
    CHECK(simulation1.gety()[370] == doctest::Approx(28.4470110688));
    CHECK(simulation1.getH()[370] == doctest::Approx(9.4607161445));

    CHECK(simulation1.getx().size() == 371);
    CHECK(simulation1.gety().size() == 371);
    CHECK(simulation1.getH().size() == 371);
    CHECK(simulation1.gett().size() == 371);
  }
}
TEST_CASE(
    " Testing the simulation given the second set of parameters and initial "
    "values") {
  // changing the values of the parameters and redoing the tests
  // setting the parameters and the initial values
  pf::Simulation simulation2;
  simulation2.setValueA(1.2);
  simulation2.setValueB(0.5);
  simulation2.setValueC(0.2);
  simulation2.setValueD(0.7);

  simulation2.setx_0(25);
  simulation2.sety_0(15);

  simulation2.initializeVectors();

  // doing tests divided in subcases
  SUBCASE("testing the values of e2_x and e2_y") {
    CHECK(simulation2.e2_x() == doctest::Approx(3.5));
    CHECK(simulation2.e2_y() == doctest::Approx(2.4));
  }

  SUBCASE("testing the initial values of x, y, and H") {
    CHECK(simulation2.getx()[0] == 25);
    CHECK(simulation2.gety()[0] == 15);
    CHECK(simulation2.getH()[0] == doctest::Approx(6.99713));
  }

  SUBCASE("testing the values of x, y, and H after 0.001") {
    simulation2.runSimulation(1);
    CHECK(simulation2.getx()[1] == doctest::Approx(24.95189));
    CHECK(simulation2.gety()[1] == doctest::Approx(15.01092));
    CHECK(simulation2.getH()[1] == doctest::Approx(6.99344));

    CHECK(simulation2.getx().size() == 2);
    CHECK(simulation2.gety().size() == 2);
    CHECK(simulation2.getH().size() == 2);
    CHECK(simulation2.gett().size() == 2);
  }

  SUBCASE("testing the values of x, y, and H after 0.003") {
    simulation2.runSimulation(3);
    CHECK(simulation2.getx()[3] == doctest::Approx(24.85574));
    CHECK(simulation2.gety()[3] == doctest::Approx(15.03269));
    CHECK(simulation2.getH()[3] == doctest::Approx(6.98606));

    CHECK(simulation2.getx().size() == 4);
    CHECK(simulation2.gety().size() == 4);
    CHECK(simulation2.getH().size() == 4);
    CHECK(simulation2.gett().size() == 4);
  }

  SUBCASE("testing the dimension of the vectors after 0.027") {
    simulation2.runSimulation(27);
    CHECK(simulation2.getx().size() == 28);
    CHECK(simulation2.gety().size() == 28);
    CHECK(simulation2.getH().size() == 28);
    CHECK(simulation2.gett().size() == 28);
  }

  SUBCASE("testing the values of x, y, and H after 0.05") {
    simulation2.runSimulation(50);
    CHECK(simulation2.getx()[50] == doctest::Approx(22.6435977623));
    CHECK(simulation2.gety()[50] == doctest::Approx(15.5047001662));
    CHECK(simulation2.getH()[50] == doctest::Approx(6.8077837714));
    CHECK(simulation2.getx().size() == 51);
    CHECK(simulation2.gety().size() == 51);
    CHECK(simulation2.getH().size() == 51);
    CHECK(simulation2.gett().size() == 51);
  }

  SUBCASE("testing the values of x, y, and H after 41") {
    simulation2.runSimulation(41000);
    CHECK(simulation2.getx()[41000] == doctest::Approx(32.3056759334));
    CHECK(simulation2.gety()[41000] == doctest::Approx(13.3331269875));
    CHECK(simulation2.getH()[41000] == doctest::Approx(7.5867265950));
    CHECK(simulation2.getx().size() == 41001);
    CHECK(simulation2.gety().size() == 41001);
    CHECK(simulation2.getH().size() == 41001);
    CHECK(simulation2.gett().size() == 41001);
  }
}
TEST_CASE(
    "testing the case in which the specie of preys goes extinct (followed by "
    "the predator specie) after a sufficient long time") {
  pf::Simulation simulation3;
  simulation3.setValueA(0.6);
  simulation3.setValueB(2.5);
  simulation3.setValueC(0.3);
  simulation3.setValueD(0.5);

  simulation3.setx_0(8);
  simulation3.sety_0(12);

  simulation3.initializeVectors();

  simulation3.runSimulation(80000);
  CHECK(simulation3.getx()[80000] == 0);
  CHECK(simulation3.gety()[80000] == 0);
}

TEST_CASE(
    "testing the case in which the species of predators goes extinct and the "
    "number of preys increases indefinitely after a sufficient long time") {
  pf::Simulation simulation4;
  simulation4.setValueA(3.0);
  simulation4.setValueB(0.005);
  simulation4.setValueC(0.0001);
  simulation4.setValueD(2.5);

  simulation4.setx_0(60);
  simulation4.sety_0(5);

  simulation4.initializeVectors();

  simulation4.runSimulation(80000);
  CHECK(simulation4.gety()[80000] == 0);
}

// testing equilibrium points
TEST_CASE("Testing equilibrium") {
  pf::Simulation simulation5;
  simulation5.setValueA(2.0);
  simulation5.setValueB(0.01);
  simulation5.setValueC(0.02);
  simulation5.setValueD(1.5);

  // testing the case in which there aren't any preys or predators
  simulation5.setx_0(0);
  simulation5.sety_0(0);
  simulation5.initializeVectors();

  simulation5.runSimulation(80000);
  CHECK(simulation5.getx()[70000] == 0);
  CHECK(simulation5.gety()[65000] == 0);
  CHECK(simulation5.getx()[700] == 0);
  CHECK(simulation5.gety()[3456] == 0);
  CHECK(simulation5.getx()[12360] == 0);
  CHECK(simulation5.gety()[5000] == 0);
}