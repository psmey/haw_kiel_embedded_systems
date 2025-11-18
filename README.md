# HAW Kiel Embedded Systems

## Tasks

### 4.6 TraceX

Add Azure RTOS ThreadX Support

https://community.st.com/t5/stm32-mcus/how-can-i-add-tracex-support-in-stm32cubeide/ta-p/49380

### 4.7.1 Critical sections

![4.7.1 Critical sections Sequential View](assets/4_7_Critical_sections_Sequential_View.png)

![4.7.1 Critical sections Time View](assets/4_7_Critical_sections_Time_View.png)

USART Output:

```
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

```
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
