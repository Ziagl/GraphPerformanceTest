## Graph Performance Test

The purpose of this program is to benchmark different types of data organisation. The question: is there a performance boost with a graph structure instead a normal class hierarchy structure and are there benefits in the data access?

The example for this is the following: create a data structure for the world soccer association. Each team consists of at least 11 players, a league of at least 10 teams, a country of at least 2 leagues and every country should have soccer leages.

Data access examples: 
   * search for a player name
   * list all players of a team
   * move player from one team to another

### Content

There are 2 Visual Studio projects included.
   * GraphPerformanceTest
     testet with Visual Studio 2019 on Windows 10 with x86 and x64
   * GraphPerformanceTestLinux
     testet with Visual Studio 2019 on Windows 10 but built and executed remotely on Linux (ARM Raspberry Pi)

### Tests

Code fully works on Windows and Linux.

### Dependencies

To built the code, you need boost library (path was added to Windows environment variable BOOST).

