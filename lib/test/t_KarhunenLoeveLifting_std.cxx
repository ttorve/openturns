//                                               -*- C++ -*-
/**
 *  @brief The test file of class KarhunenLoeveLifting
 *
 *  Copyright 2005-2017 Airbus-EDF-IMACS-Phimeca
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include "openturns/OT.hxx"
#include "openturns/OTtestcode.hxx"
#include <cmath>

using namespace OT;
using namespace OT::Test;

int main(int argc, char *argv[])
{
  TESTPREAMBLE;
  OStream fullprint(std::cout);
  setRandomGenerator();

  try
  {
    Mesh mesh(IntervalMesher(Indices(1, 9)).build(Interval(-1.0, 1.0)));
    AbsoluteExponential cov1D(Point(1, 1.0));
    KarhunenLoeveP1Algorithm algo(mesh, cov1D, 0.0);
    algo.run();
    KarhunenLoeveResult result(algo.getResult());
    KarhunenLoeveLifting lifting(result);
    fullprint << "lifting=" << lifting << std::endl;
    /* Get the input and output description */
    fullprint << "lifting input description=" << lifting.getInputDescription() << std::endl;
    fullprint << "lifting output description=" << lifting.getOutputDescription() << std::endl;
    /* Get the input and output dimension */
    fullprint << "lifting input dimension=" << lifting.getInputDimension() << std::endl;
    fullprint << "lifting output dimension=" << lifting.getOutputDimension() << std::endl;
    Point point(lifting.getInputDimension(), 1.0);
    Field field(lifting(point));
    fullprint << "point=" << point << std::endl;
    fullprint << "field=" << field << std::endl;
    /* Get the number of calls */
    fullprint << "called " << lifting.getCallsNumber() << " times" << std::endl;
  }
  catch (TestFailed & ex)
  {
    std::cerr << ex << std::endl;
    return ExitCode::Error;
  }


  return ExitCode::Success;
}

