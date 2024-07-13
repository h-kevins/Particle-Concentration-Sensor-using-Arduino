
 % This code reads data from an Arduino connected to the computer via a serial port and writes it to a file.
 % It waits for the Arduino to send a specific character indicating readiness before starting data acquisition.
 % The acquired data is then written to a file specified by the user.
 % 
 % @note Make sure to adjust the value of `numLines` variable to the number of lines you want to read from the Arduino.
 % 
 % @warning This code assumes that the Arduino is connected to the COM3 port and is configured to send data at a baud rate of 9600.
 % 
 % @throws An error is thrown if the file fails to open for writing.
 % 
 % @param None.
 % 
 % @return None.
 %
 % @author Kevin Hernandez
 %


% Create serial port object using serialport
serObj = serialport('COM3', 9600);

try
    % Wait for Arduino to send 'a' indicating readiness
    disp('Waiting for Arduino...');
    ArduinoReady = char(readline(serObj));
    while ArduinoReady ~= 'a'
        ArduinoReady = char(readline(serObj));
    end
    disp('Arduino is ready.');

    % Define file name
    filename = 'data.txt';

    % Open file for writing
    fileID = fopen(filename, 'w');
    
    % Check if file is opened successfully
    if fileID == -1
        error('Failed to open file for writing.');
    end

    % Define number of lines to read
    numLines = 2500; % Adjust this to the number of lines you want to read

    % Get current timestamp
    timestamp = datestr(now, 'yyyy-mm-dd HH:MM:SS.FFF');
    % Write the timestamp
    fprintf(fileID, '%s\n',"# " + timestamp);

    % Read data from Arduino and write to file
    disp('Data acquisition starting...');
    for line = 1:numLines
        % Read line from Arduino
        dataLine = char(readline(serObj));
        
        
        
        % Write data to file
        fprintf(fileID, '%s\n', dataLine);
        disp("Writing line...(" + line + "/"+ numLines +")");
    end
    disp('Data acquisition complete.');
    

    % Get current timestamp
    timestamp = datestr(now, 'yyyy-mm-dd HH:MM:SS.FFF');
    % Write the timestamp
    fprintf(fileID, '%s\n', "# " + timestamp);

    % Close the file
    fclose(fileID);
    disp('Data written to file.');

catch ME
    disp(['Error: ' ME.message]);
end

% Close serial port
delete(serObj);
disp('Serial port closed.');
