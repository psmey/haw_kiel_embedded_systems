# HAW Kiel Embedded Systems

## Table of Contents

- [Table of Contents](#table-of-contents)
- [Exercise 1](#exercise-1)
  - [4.6 TraceX](#46-tracex)
  - [4.7.1 Critical sections](#471-critical-sections)
  - [4.7.2 Thread runtime \& Critical Sections](#472-thread-runtime--critical-sections)
  - [4.7.3. Critical section – USART](#473-critical-section--usart)
  - [4.8. Queues](#48-queues)
  - [4.9. Thread priorities \& Preemption](#49-thread-priorities--preemption)
    - [Case 0 – Round-Robin Scheduling \& Same Priority](#case-0--round-robin-scheduling--same-priority)
    - [Case 1 – Preemptive Scheduling](#case-1--preemptive-scheduling)
    - [Case 2 – Round-Robin Scheduling \& Same Priority](#case-2--round-robin-scheduling--same-priority)
    - [Case 3 – Preemption-Threshold Scheduling](#case-3--preemption-threshold-scheduling)
- [Exercise 2](#exercise-2)
  - [4.1 Memory pool – Gatekeeper](#41-memory-pool--gatekeeper)

## Exercise 1

### 4.6 TraceX

Add Azure RTOS ThreadX Support

<https://community.st.com/t5/stm32-mcus/how-can-i-add-tracex-support-in-stm32cubeide/ta-p/49380>

### 4.7.1 Critical sections

![4.7.1 Critical sections Sequential View](assets/4_7_Critical_sections_Sequential_View.png)

![4.7.1 Critical sections Time View](assets/4_7_Critical_sections_Time_View.png)

USART Output:

```txt
Slow thread cycle: 40 ticks
Speedy thread cycle: 14 ticks
Speedy thread cycle: 14 ticks
Speedy thread cycle: 14 ticks
Slow thread cycle: 40 ticks
Speedy thread cycle: 14 ticks
Speedy thread cycle: 14 ticks
Speedy thread cycle: 14 ticks
Slow thread cycle: 40 ticks
Speedy thread cycle: 14 ticks
Speedy thread cycle: 14 ticks
Speedy thread cycle: 14 ticks
...
```

### 4.7.2 Thread runtime & Critical Sections

![4.7.2 Thread runtime & Critical Sections](assets/4_7_2_Thread_runtime_Critical_Sections.png)

USART Output

```txt
Slow thread cycle: 43 ticks
Speedy thread cycle: 22 ticks
Speedy thread cycle: 21 ticks
Slow thread cycle: 43 ticks
Speedy thread cycle: 22 ticks
Speedy thread cycle: 21 ticks
Slow thread cycle: 43 ticks
Speedy thread cycle: 22 ticks
Speedy thread cycle: 21 ticks
...
```

### 4.7.3. Critical section – USART

![4.7.3. Critical section – USART](assets/4_7_3_Critical_section_USART.png)

![4.7.3. Critical section – USART HTerm](assets/4_7_3_Critical_section_USART_HTerm.png)

### 4.8. Queues

![4.8. Queues](assets/4_8_Queues.png)

![4.8. Queues HTerm](assets/4_8_Queues_HTerm.png)

### 4.9. Thread priorities & Preemption

#### Case 0 – Round-Robin Scheduling & Same Priority

![4.9. Thread priorities & Preemption Case 0 – Round-Robin Scheduling](assets/4_9_Thread_priorities_Preemption_case_0.png)

#### Case 1 – Preemptive Scheduling

![4.9. Thread priorities & Preemption Case 1 – Preemptive Scheduling](assets/4_9_Thread_priorities_Preemption_case_1.png)

#### Case 2 – Round-Robin Scheduling & Same Priority

It's the same as case 0.

![4.9. Thread priorities & Preemption Case 2 – Round-Robin Scheduling](assets/4_9_Thread_priorities_Preemption_case_0.png)

#### Case 3 – Preemption-Threshold Scheduling

![4.9. Thread priorities & Preemption Case 3 – Preemption-Threshold Scheduling](assets/4_9_Thread_priorities_Preemption_case_3.png)

## Exercise 2

### 4.1 Memory pool – Gatekeeper

![4.1 Memory pool – Gatekeeper HTerm](assets/4_1_Memory_pool_Gatekeeper_HTerm.png)

![4.1 Memory pool – Gatekeeper](assets/4_1_Memory_pool_Gatekeeper.png)
