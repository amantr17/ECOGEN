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

#ifndef CELLO2_H
#define CELLO2_H

#include "../Order1/Cell.h"
#include "CellInterfaceO2.h"

class CellO2 : public Cell
{
    public:
        CellO2();
        CellO2(int lvl); //Pour AMR
        virtual ~CellO2();
        virtual void allocate(const std::vector<AddPhys*>& addPhys);
        virtual void copyPhase(const int& phaseNumber, Phase* phase);
        virtual void computeLocalSlopes(CellInterface& cellInterfaceRef, Limiter& globalLimiter, Limiter& interfaceLimiter,
            Limiter& globalVolumeFractionLimiter, Limiter& interfaceVolumeFractionLimiter,
            double& alphaCellAfterOppositeSide, double& alphaCell, double& alphaCellOtherInterfaceSide, double& epsInterface);
        virtual void computeLocalSlopesLimite(CellInterface& cellInterfaceRef, Limiter& globalLimiter,
            Limiter& interfaceLimiter, Limiter& globalVolumeFractionLimiter, Limiter& interfaceVolumeFractionLimiter,
            double& epsInterface);
        virtual void saveCons();
        virtual void recuperationCons();
        virtual void predictionOrdre2(const double& dt, Symmetry* symmetry);
        virtual void fulfillState(Prim type = vecPhases);

        //Accesseurs
        virtual Phase* getPhase(const int& phaseNumber, Prim type = vecPhases) const;
        virtual Phase** getPhases(Prim type = vecPhases) const;
        virtual Mixture* getMixture(Prim type = vecPhases) const;
        virtual Transport& getTransport(const int& numTransport, Prim type = vecPhases) const;
        virtual Transport* getTransports(Prim type = vecPhases) const;
        virtual void setTransport(double value, int& numTransport, Prim type = vecPhases);

        //Pour methode AMR
        virtual void createChildCell(const int& lvl);                                              /*!< Creer une cell enfant (non initializee) */

        //Pour methodes ordre 2 parallele
        virtual void fillBufferSlopes(double* buffer, int& counter, const int& lvl, const int& neighbour) const;

    protected:
        Phase** m_vecPhasesO2;                  /*!< pour stocker les values predites a l ordre 2 */
        Mixture* m_mixtureO2;                   /*!< pour stocker les values predites a l ordre 2 */
        Transport* m_vecTransportsO2;		        /*!< pour stocker les values predites a l ordre 2 */
        Flux* m_consSauvegarde;                 /*!< Vector de save des variables conservatives. De type flux car recueille la somme des flux sur l objet cell */
        Transport* m_consTransportsSauvegarde;  /*!< Vector de saugevarde des grandeurs passives permettant de recueillir la somme des flux des grandeurs transportees */

    private:
};

#endif // CELLO2_H
