.. _dfrobot_sim7000_shield:

DFRobot SIM7000 NB-IoT/Cat-M/GPRS Expansion Shield
###################################################

Overview
********

The `DFRobot SIM7000 Expansion Shield`_ is an Arduino Uno R3 form-factor
shield built around the SimCom SIM7000 NB-IoT/Cat-M1/GPRS modem.

In Zephyr this shield is modeled as a modem device using the
``simcom,sim7000`` compatible over the Arduino UART
(``arduino_serial``). The modem's power key line is connected to
Arduino pin D12, active low.

Requirements
************

This shield requires a board that provides the ``arduino_serial`` and
``arduino_header`` devicetree aliases.

Programming
***********

Set ``-DSHIELD=dfrobot_sim7000`` when invoking ``west build``. For
example, with the :zephyr:code-sample:`cellular-modem` sample:

.. zephyr-app-commands::
   :zephyr-app: samples/net/cellular_modem
   :board: disco_l475_iot1
   :shield: dfrobot_sim7000
   :goals: build

References
**********

.. _DFRobot SIM7000 Expansion Shield: https://mikroelectron.com/product/me-3494
