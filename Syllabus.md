### DESCRIPTION: This file demonstrates the learning courses in this Specialization.

### SPECIALIZATION: "Real-Time Embedded Systems".

#### Course 1: Real-Time Embedded Systems Concepts and Practices
Week 1: Exploration of RT Challenges and Concepts\
Week 2: Quality of Service Theory from Best Effort to Hard Real-Time\
Week 3: Scheduling and Concept of Real-Time Services\
Week 4: Overview of Real-time Hardware Architectures and Software Stacks\

- Course 1 Description: In this course, students will design and build a microprocessor-based embedded system application using a real-time operating system or RT POSIX extensions with Embedded Linux. The course focus is on the process as well as fundamentals of integrating microprocessor-based embedded system elements for digital command and control of typical embedded hardware systems.
- Lab Description: The course requires the student to install embedded Linux on the Raspberry Pi ARM A-Series System-on-Chip processor.  This course must be completed using a Raspberry Pi as an embedded system (headless) not a PC running Linux. You will however find Linux as a useful host development system or Windows with an SSH terminal access tool such as Putty, MobaXterm, or equivalent.
			
#### Course 2: Real-Time Embedded Systems Theory and Analysis
Week 1: Real-Time Scheduling and Rate Monotonic Least Upper Bound Derivation\
Week 2: Service Design Feasibility Analysis Practice and Methods of Implementation\
Week 3: Dynamic priority Earliest Deadline First and Least Laxity First\
Week 4: Synchronization and Bounded vs. Unbounded Blocking

- Course 2 Description: This course provides an in-depth and full mathematical derivation and review of models for scheduling policies and feasibility determination by hand and with rate monotonic tools along with comparison to actual performance for real-time scheduled threads running on a native Linux system. By the end of this course the learner will be able to full derive the fixed priority rate monotonic least upper bound for feasibility as well as justifying the rate monotonic policy and will be able to compare to dynamic priority scheduling including earliest deadline first and least laxity policies.
- At the end of this course learners will be able to fully derive and explain the math model for the rate monotonic least upper bound as well as performing timing diagram analysis for fixed and dynamic priority software services.  Tools to provide analysis will be learned (Cheddar) to automate timing analysis and to compare to actual performance.

Specific objectives include:
  - Rate monotonic theory (complete math models).
  - Differences between fixed priority rate monotonic policy and dynamic priority earliest deadline first and least laxity policies.
  - Scheduling theory and practice writing code for multi-frequency executives, priority preemptive RTOS services, and real-time threaded services on traditional operating systems (Linux).
  - Building a simple Linux multi-service system using POSIX real-time extensions on Raspberry Pi 3b using sequencing and methods to log and verify agreement between theory and practice.
  - Timing diagram generation and analysis using Cheddar.				
