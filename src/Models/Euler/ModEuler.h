//  
//       ,---.     ,--,    .---.     ,--,    ,---.    .-. .-. 
//       | .-'   .' .')   / .-. )  .' .'     | .-'    |  \| | 
//       | `-.   |  |(_)  | | |(_) |  |  __  | `-.    |   | | 
//       | .-'   \  \     | | | |  \  \ ( _) | .-'    | |\  | 
//       |  `--.  \  `-.  \ `-' /   \  `-) ) |  `--.  | | |)| 
//       /( __.'   \____\  )---'    )\____/  /( __.'  /(  (_) 
//      (__)              (_)      (__)     (__)     (__)     
//      Official webSite: https://code-mphi.github.io/ECOGEN/
//
//  This file is part of ECOGEN.
//
//  ECOGEN is the legal property of its developers, whose names 
//  are listed in the copyright file included with this source 
//  distribution.
//
//  ECOGEN is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published 
//  by the Free Software Foundation, either version 3 of the License, 
//  or (at your option) any later version.
//  
//  ECOGEN is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with ECOGEN (file LICENSE).  
//  If not, see <http://www.gnu.org/licenses/>.

#ifndef MODEULER_H
#define MODEULER_H

#include "../Model.h"
#include "../../Order1/Cell.h"
#include "FluxEuler.h"
#include "MixEuler.h"

//! \class     ModEuler
//! \brief     Model class for Euler mathematical system of equations (single phase)
class ModEuler : public Model
{
  public:
    //! \brief     Euler model constructor
    //! \param     numbTransports      number of additional transport equations
    ModEuler(const int& numbTransports);
    virtual ~ModEuler();

    virtual void allocateCons(Flux** cons);
    virtual void allocatePhase(Phase** phase);
    virtual void allocateMixture(Mixture** mixture);

    //! \details    Complete single fluid state from pressure, density and velocity
    virtual void fulfillState(Phase** phases, Mixture* /*mixture*/);

    //! \details    Does nothing for this model
    virtual void fulfillStateRestart(Phase** /*phases*/, Mixture* /*mixture*/) {};

    //! \details    Does nothing for this model
    virtual void initializeAugmentedVariables(Cell* /*cell*/) {};

    //Hydrodynamic Riemann solvers
    //----------------------------
    virtual void solveRiemannIntern(Cell& cellLeft, Cell& cellRight, const double& dxLeft, const double& dxRight, double& dtMax, std::vector<double> &boundData = DEFAULT_VEC_INTERFACE_DATA) const; 
    virtual void solveRiemannWall(Cell& cellLeft, const double& dxLeft, double& dtMax, std::vector<double> &boundData) const; 
    virtual void solveRiemannInflow(Cell& cellLeft, const double& dxLeft, double& dtMax, const double m0, const double* /*ak0*/, const double* rhok0, const double* pk0, std::vector<double> &boundData) const;
    virtual void solveRiemannSubInj(Cell& cellLeft, const double& dxLeft, double& dtMax, const double m0, const double* Tk0, const double* /*ak0*/, std::vector<double> &boundData) const;
    virtual void solveRiemannTank(Cell& cellLeft, const double& dxLeft, double& dtMax, const double* /*ak0*/, const double* rhok0, const double& p0, const double& /*T0*/, std::vector<double> &boundData) const;
    virtual void solveRiemannOutflow(Cell& cellLeft, const double& dxLeft, double& dtMax, const double p0, std::vector<double> &boundData) const; 
    virtual void solveRiemannNullFlux() const;

    virtual void reverseProjection(const Coord normal, const Coord tangent, const Coord binormal) const;

    //low-Mach preconditioning
    //------------------------
    virtual void lowMachSoundSpeed(double& machRef, const double& uL, double& cL, const double& uR = Errors::defaultDouble, double& cR = Tools::uselessDouble) const;
    virtual void setLowMach(const bool& lowMach) { m_lowMach = lowMach; };

    //Accessors
    //---------
    virtual const double& getSM();
    virtual const Coord& getVelocity(const Cell* cell) const { return cell->getPhase(0)->getVelocity(); };
    virtual Coord& getVelocity(Cell* cell) { return cell->getPhase(0)->getVelocity(); };

    virtual const std::string& whoAmI() const { return m_name; };
    
    virtual void setSmoothCrossSection1d(const bool& applySmooth) { m_smoothCrossSection1d = applySmooth; };
  
  protected:

  private:
    static const std::string NAME;
};

#endif // MODEULER_H
