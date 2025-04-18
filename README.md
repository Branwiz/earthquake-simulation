Earthquake Simulation in C

This project is a terminal-based simulation that visualizes the buildup of tectonic stress across a 2D grid representing the Earth's surface. Fault lines are drawn interactively by the user, and the simulation proceeds until one or more points on the grid experience an earthquake (stress level >= 200). The final project includes an IEEE-style report and a demo video explaining the simulation logic, coding approach, and key insights.

🚀 Features

Interactive fault line creation using keyboard input

Real-time color-coded terminal visualization using ANSI escape codes

Simulation logic mimicking tectonic stress buildup and earthquake triggering

Edge case handling and data integrity safeguards

Final report written in IEEE LaTeX format

High-quality YouTube demo video included

📄 How It Works

The user draws fault lines on the grid using shapes

Entering -1 begins the simulation loop

Each grid point updates stress based on whether it lies on a fault line

The grid is printed with green, yellow, or red color codes representing stress levels

Once a point reaches a stress level of 200 or more, an earthquake is triggered and the final display is shown

💡 Key Learning Outcomes

Mastery of 2D arrays and structs in C

ANSI escape code integration for live terminal updates

Debugging and edge case handling in systems-level simulations

Workflow planning, report writing in LaTeX, and public-facing documentation

## 🎥 Demo Video

[![Watch the video](https://img.youtube.com/vi/APWTrnyLl7o/0.jpg)](https://www.youtube.com/watch?v=APWTrnyLl7o)

📑 Report

An IEEE-format report is included in the /report directory, containing:

Project summary and motivation

Simulation workflow and logic diagrams

Experimental results and corner case testing

Takeaways and conclusions

⚖️ License

This project is open-source under the MIT License. Feel free to use, modify, or contribute.

📅 Author

Brandon Proano

B.S. Computer Engineer @ University of Central Florida

Mark Cuban Foundation AI Bootcamp Alumnus



Feel free to fork, star, or contribute to this repository!
