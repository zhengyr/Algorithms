MapFile   = 'BrandeisMapLabeled.jpg';
RouteFile = 'Route.txt';

%Display the map:
Map = imread(MapFile);
imshow(Map,'Border','tight');
hold on

%Load the path data:
P = load(RouteFile);

%Make the plot orgin the upper left corner:
axis ij

%Plot the route using color magenta:
x=[P(:,1) P(:,3)];
y=[P(:,2) P(:,4)];
plot(x',y','m','LineWidth',4);
