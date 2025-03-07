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

#ifndef MIXUEQTOTENERGY_H
#define MIXUEQTOTENERGY_H

#include <vector>
#include "../Mixture.h"

//! \class     MixUEqTotEnergy
//! \brief     Mixture variables for the velocity-equilibrium system of equations
class MixUEqTotEnergy : public Mixture
{
  public:
    MixUEqTotEnergy();
    //! \brief     Mixture constructor from a XML format reading
    //! \details   Reading data from XML file under the following format:
    //!           ex: <mixture>
    //!                 <velocity x = "0." y = "0." z = "0." />
    //!               </mixture>
    //! \param     state           XML element to read for mixture data
    //! \param     fileName       string name of readed XML file
    MixUEqTotEnergy(tinyxml2::XMLElement* state, std::string fileName);
    virtual ~MixUEqTotEnergy();

    virtual void allocateAndCopyMixture(Mixture** mixture);
    virtual void copyMixture(Mixture &mixture);
    virtual double computeDensity(const double* alphak, const double* rhok);
    virtual double computePressure(const double* alphak, const double* pk);
    virtual double computeInternalEnergy(const double* Yk, const double* ek);
    virtual double computeFrozenSoundSpeed(const double* Yk, const double* ck);
    
    virtual void computeMixtureVariables(Phase** vecPhase);
    virtual void internalEnergyToTotalEnergy(std::vector<QuantitiesAddPhys*>& /*vecGPA*/) {};
    virtual void totalEnergyToInternalEnergy(std::vector<QuantitiesAddPhys*>& /*vecGPA*/) {};

    virtual void localProjection(const Coord& normal, const Coord& tangent, const Coord& binormal);
    virtual void reverseProjection(const Coord& normal, const Coord& tangent, const Coord& binormal);

    //Data printing
    virtual int getNumberScalars() const { return numberScalarsMixture; };
    virtual int getNumberVectors() const { return 1; };
    virtual double returnScalar(const int& numVar) const;
    virtual Coord returnVector(const int& numVar) const;
    virtual std::string returnNameScalar(const int& numVar) const;
    virtual std::string returnNameVector(const int& numVar) const;

    //Data reading
    virtual void setScalar(const int& numVar, const double& value);
    virtual void setVector(const int& numVar, const Coord& value);

    //Parallel
    virtual int numberOfTransmittedVariables() const;
    virtual void fillBuffer(double* buffer, int& counter) const;
    virtual void fillBuffer(std::vector<double>& dataToSend) const;
    virtual void getBuffer(double* buffer, int& counter);
    virtual void getBuffer(std::vector<double>& dataToReceive, int& counter);

    //Second order
    virtual void computeSlopesMixture(const Mixture &sLeft, const Mixture &sRight, const double& distance);
    virtual void setToZero();
    virtual void extrapolate(const Mixture &slope, const double& distance);
    virtual void limitSlopes(const Mixture &slopeGauche, const Mixture &slopeDroite, Limiter& globalLimiter);

    //Parallel second order
    virtual int numberOfTransmittedSlopes() const;
    virtual void fillBufferSlopes(double* buffer, int& counter) const;
    virtual void getBufferSlopes(double* buffer, int& counter);

    //Accessors
    virtual const double& getDensity() const { return m_density; };
    virtual const double& getPressure() const { return m_pressure; };
    virtual const double& getU() const { return m_velocity.getX(); };
    virtual const double& getV() const { return m_velocity.getY(); };
    virtual const double& getW() const { return m_velocity.getZ(); };
    virtual const Coord& getVelocity() const { return m_velocity; };
    virtual Coord& getVelocity() { return m_velocity; };
    virtual const double& getFrozenSoundSpeed() const { return m_frozenSoundSpeed; };
    virtual const double& getWoodSoundSpeed() const { return m_woodSoundSpeed; };

    virtual void setPressure(const double& p);
    virtual void setVelocity(const double& u, const double& v, const double& w);
    virtual void setVelocity(const Coord& vit);
    virtual void setU(const double& u);
    virtual void setV(const double& v);
    virtual void setW(const double& w);

    //Operators
    virtual void changeSign();
    virtual void multiplyAndAdd(const Mixture &slopesMixtureTemp, const double& coeff);
    virtual void divide(const double& coeff);

  protected:
    double m_density;              //!< mixture density
    double m_pressure;             //!< mixture pressure
    Coord m_velocity;              //!< mixture velocity
    double m_frozenSoundSpeed;     //!< frozen sound speed
    double m_woodSoundSpeed;       //!< wood sound speed
};

#endif // MIXUEQTOTENERGY_H
