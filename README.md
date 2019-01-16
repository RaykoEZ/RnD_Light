# RnD_Light
Test Environment for RnD in UE4.20

#### This project captures distance data from viewing a vehicle in a simulated nighttime environment.
> Collected data is stored in Content/Data/ as .csv and excel worksheet files.

For more info regarding the experiment, please check the .pdf file in root.

#### For details regarding exporting in-game data to .csv:
- A C++ class - "CSVExporter", is used to create a raw text file with the .csv format 
- The said C++ class uses the input data set from an array of data collected at runtime, on the blueprint level.
