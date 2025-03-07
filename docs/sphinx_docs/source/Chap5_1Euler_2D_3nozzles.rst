.. role:: xml(code)
  :language: xml

*******
Nozzles
*******

Nozzles are pipes or tubes of variable cross sections. It can control the direction or characteristics of a fluid flow. 

Here, tests are divided into 3 categories: 

- Tank with shock.
- Supersonic injection.
- Subsonic injection.

Tank with shock
---------------

It means that there is a shock in the tank which is placed before the nozzle. Initial conditions are described in :numref:`Fig:testCases:Euler:TankwithShockIni`. This test is referenced in *./libTests/referenceTestCases/euler/2D/nozzles/tankWithShock/*. The corresponding uncommented line in *ECOGEN.xml* is: 

.. code-block:: xml

  <testCase>./libTests/referenceTestCases/euler/2D/nozzles/tankWithShock/</testCase>

.. _Fig:testCases:Euler:TankwithShockIni:

.. figure:: ./_static/testCases/Euler/Nozzles/NozzleTankShockInitial.*
  :scale: 60%
  :align: center

  Initial helium conditions before the nozzle.

+-----------------------------+-------------------------------+
| Characteristic              | Value                         |
+=============================+===============================+
| Dimension                   | L=1m, Øa=0.20m, Ømin=0.17m    |
+-----------------------------+-------------------------------+
| Initial mesh structure :    | unstructured                  |
+-----------------------------+-------------------------------+
| Boundary conditions         | tank, wall, outflow, wall     |
+-----------------------------+-------------------------------+
| Final solution time         | 1.44e-2 s                     |
+-----------------------------+-------------------------------+
| Solution printing frequency | 7.2e-4 s                      |
+-----------------------------+-------------------------------+

Results are shown in :numref:`Fig:testCases:Euler:TankwithShockAnim`.
When helium arrives in the minimal section, there is a sonic flow. So, at the divergent section, one observes a shock wave, and then, pressure becomes stationary.

.. _Fig:testCases:Euler:TankwithShockAnim:

.. figure:: ./_static/testCases/Euler/Nozzles/NozzleTankShockAnim.*
  :scale: 65%
  :align: center

  Pressure evolution in the nozzle over time. Visualization using Paraview_ software.

The numerical solution is compared against an analytical solution in :numref:`Fig:testCases:Euler:TankwithShockComp`.

.. _Fig:testCases:Euler:TankwithShockComp:

.. figure:: ./_static/testCases/Euler/Nozzles/NozzleTankShockComp.*
  :scale: 80%
  :align: center

  Comparison between numerical and analytical pressure evolution in the nozzle over the x-direction. Visualization using Python_.

The numerical solution is close to the analytical solution. Although differences exist, one should note that the code giving the analytical solution is 1D, whereas the numerical solution is 2D. Differences are therefore expected. Indeed, the 1D analytical solution cannot fully take into account the bent shock wave in the nozzle, unlike the 2D numerical solution. Also, the more the nozzle section varies, the less the analytical solution is accurate.

Pressure differences are shown in :numref:`Fig:testCases:Euler:TankwithShockE`.

.. _Fig:testCases:Euler:TankwithShockE:

.. figure:: ./_static/testCases/Euler/Nozzles/NozzleTankShockE.*
  :scale: 80%
  :align: center

  Pressure difference between numerical and analytical pressures over the x-direction. Visualization using Python_.

Maximum pressure differences are located at the ends of the nozzle and the minimum pressure difference is located at the minimum section.


Supersonic injection
--------------------

Before the nozzle, one injects helium with Mach > 1. Therefore, helium flow is supersonic and will cross the nozzle. This test is referenced in *./libTests/referenceTestCases/euler/2D/nozzles/supersonicInjection/*. The corresponding uncommented line in *ECOGEN.xml* is:

.. code-block:: xml

  <testCase>./libTests/referenceTestCases/euler/2D/nozzles/supersonicInjection/</testCase>

........


Subsonic injection
------------------

Before the nozzle, one injects air with Mach < 1. Therefore, air flow is subsonic and will cross the nozzle. Initial conditions are described on figures :numref:`Fig:testCases:Euler:subsonicIni` and :numref:`Fig:testCases:Euler:subsupersonicIni`. This test is referenced in *./libTests/referenceTestCases/euler/2D/nozzles/subsonicInjection/*. The corresponding uncommented line in *ECOGEN.xml* is: 

.. code-block:: xml

  <testCase>./libTests/referenceTestCases/euler/2D/nozzles/subsonicInjection/</testCase>

+-----------------------------+---------------------------------+
| Characteristic              | Value                           |
+=============================+=================================+
| Dimension                   | L=1m, Øa=0.2m, Ømin=0.17m       |
+-----------------------------+---------------------------------+
| Initial mesh structure :    | unstructured                    |
+-----------------------------+---------------------------------+
| Boundary conditions         |subinjection, wall, outflow, wall|
+-----------------------------+---------------------------------+
| Final solution time         | 1s                              |
+-----------------------------+---------------------------------+
| Solution printing frequency | 0.25s                           |
+-----------------------------+---------------------------------+

.. _Fig:testCases:Euler:subsonicIni:

.. figure:: ./_static/testCases/Euler/Nozzles/subsubsonicInitial.*
  :scale: 31%
  :align: center

  Initial air conditions before the nozzle with subsonic outlet flow.


.. _Fig:testCases:Euler:subsupersonicIni:

.. figure:: ./_static/testCases/Euler/Nozzles/subsupsonicInitial.*
  :scale: 31%
  :align: center

  Initial air conditions before the nozzle with supersonic outlet flow.


Another configuration is possible. Even thought shock wave happens in the divergent, the flow will be subsonic, otherwise, the flow will be supersonic at the exit. It depends on the critical pressure ratio.

This case is when the flow is supersonic at the exit (:numref:`Fig:testCases:Euler:subsupersonic`).

.. _Fig:testCases:Euler:subsupersonic:

.. figure:: ./_static/testCases/Euler/Nozzles/subsup.*
  :scale: 70%
  :align: center

  Air velocity inside a nozzle with supersonic exit. Visualization using Paraview_ software.

.. figure:: ./_static/testCases/Euler/Nozzles/supToggle.*
  :scale: 40%
  :align: center
  
Here, the nozzle is primed at the minimal section. So, at the exit, one observes that the flow is supersonic.

This is the other case, when the flow is subsonic at the exit (:numref:`Fig:testCases:Euler:subsubsonic`).

.. _Fig:testCases:Euler:subsubsonic:

.. figure:: ./_static/testCases/Euler/Nozzles/subsub.*
  :scale: 65%
  :align: center

  Air velocity inside a nozzle with subsonic exit. Visualization using Paraview_ software.

.. figure:: ./_static/testCases/Euler/Nozzles/subToggle.*
  :scale: 57%
  :align: center

Because of a subsonic flow over the whole nozzle, it is not primed at the throat. Thus, one notices that the fluid accelerates when the section is reduced, then slows down when the section is enlarged. This is due to the conservation of the mass flow. 

.. _Paraview: https://www.paraview.org/
.. _gnuplot: http://www.gnuplot.info/
.. _Python: https://www.python.org/
