% Arduino Data Acquisition and Logging Script
%
% This script reads data from an Arduino connected to the computer via a
% serial port and writes it to a file.
%
% Usage:
%   Adjust the variables `port` and `baudrate` according to your Arduino
%   configuration. Ensure the Arduino is ready to send data before running
%   the script.
%
% Parameters:
%   None.
%
% Returns:
%   None.
%
% Author: Kevin Hernandez


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
