
Smart House Control System Readme

This C program implements a Smart House Control System, providing automated and user-controlled functionalities for monitoring and managing various aspects of a smart home. The system utilizes multithreading to concurrently handle user input, fire monitoring, flood monitoring, and damage monitoring.

Functionalities:

User Control Thread:

The program features a dedicated thread for user input, allowing users to interact with the system and control different parameters of the house, such as water temperature, air temperature, lights, coffee machine, sauna, cameras, and gates.
Users can input commands like 'water', 'air', 'lights', 'coffee', 'sauna', 'cameras', 'gate', and 'exit' to adjust corresponding parameters.
Monitoring Threads:

The system includes three monitoring threads:
Fire Monitoring Thread: Periodically checks for the presence of fire by generating random values and reading from a file. If fire is detected, it activates fire safety protocols.
Flood Monitoring Thread: Periodically checks for the possibility of flooding by generating random values and reading from a file. If flooding is detected, it activates flood safety protocols.
Damage Monitoring Thread: Periodically checks for damage by generating random values and reading from a file. If damage is detected, it activates damage safety protocols.
Safety Protocols:

When any of the monitoring threads detects a potential issue (fire, flood, or damage), it triggers safety protocols, printing messages to notify users. The safety protocols are repeated three times to ensure visibility.
File Operations:

The program writes the initial state of the house to a file called "house_info.txt," providing a record of the starting values for water temperature, air temperature, sauna temperature, and the status of lights, cameras, coffee machine, and gates.
Upon user exit, the program writes the changed values to a new file called "house_updated.txt," capturing the modifications made during the user control session.
Usage:

The main function initializes and creates threads for user control and monitoring.
Users can input commands to adjust various parameters or exit the system.
Monitoring threads continuously check for potential issues and activate safety protocols if necessary.
Dependencies:

The program utilizes the pthread library for multithreading, standard C libraries for file operations, and sleep() for thread pauses.
Files:

fire_check.txt, inondation_check.txt, damage_check.txt: Files storing random values used for monitoring.
house_info.txt: File capturing the initial state of the house.
house_updated.txt: File recording changes made during user control.
Compilation:

The program can be compiled using a standard C compiler (e.g., gcc) with the necessary libraries.
Execution:

Run the compiled executable to initiate the Smart House Control System.
Follow on-screen prompts to interact with the system.
Note:

Ensure that the required dependencies are installed before compiling and running the program.
Monitor the generated output files for information on the state of the house and any changes made during user control.
