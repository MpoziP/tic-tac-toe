#include <iostream>
#include <cmath>
#include <tuple>
#include <vector>
#include <string>
using namespace std;

class PlayerInfo {
    private:
        std::string playerName;
        string playerSign;

    public:
        // Constructor to initialize values
        PlayerInfo(const std::string& name, const std::string& sign) 
        : playerName(name), playerSign(sign) {}

        // Getter functions
        std::string getPlayerName() const { return playerName; }
        std::string getPlayerSign() const { return playerSign; }

        // Function to display the players information
        void displayPlayerInfo() const {
            std:: cout << "Player: " << playerName << " - plays with sign: " << playerSign << endl;
        }

        // Static function to create a list of players
        static std::vector<PlayerInfo> createPlayers() {

            std::vector<PlayerInfo> players;

            for (int i = 0; i < 2; i++) {
                std::string name;
                std::string sign;

                std::cout << "Enter player " << i + 1 << " name: ";
                std::cin >> name;

                std::cout << "Enter player " << i + 1 << " sign: ";
                std::cin >> sign;

                players.emplace_back(name, sign);
            }

            return players;
        }
};

class Game {
    private:
        std::vector<PlayerInfo> players;
        std::string dataGrid[3][3];

    public:
        // Constructor to initialize players
        Game (const std::vector<PlayerInfo>& players) : players(players) {}

        static std::vector<Game> createGame() {
            std::vector<Game> game;

            // Initialize players information
            std::vector<PlayerInfo> players = PlayerInfo::createPlayers();

            // Initialize the game with empty grid of strings
            std::string dataGrid[3][3] = {
                {"-", "-", "-"},
                {"-", "-", "-"},
                {"-", "-", "-"}
            };

            game.emplace_back(players, dataGrid);

            return game;
        }

        // Function to print the grid
        void displayGrid() const {
            cout << "+-----------+" << endl;
            cout << "| " << dataGrid[0][0] << " | " << dataGrid[0][1] << " | " << dataGrid[0][2] << " |" << endl;
            cout << "|---|---|---|" << endl;
            cout << "| " << dataGrid[1][0] << " | " << dataGrid[1][1] << " | " << dataGrid[1][2] << " |" << endl;
            cout << "|---|---|---|" << endl;
            cout << "| " << dataGrid[2][0] << " | " << dataGrid[2][1] << " | " << dataGrid[2][2] << " |" << endl;
            cout << "+-----------+" << endl;
        }

        void playerMove(PlayerInfo& player) {

            cout << "Player: " << player.getPlayerName() << " enter cell: " << endl;

            int x, y;
            while(true) {
                cin >> x >> y;

                if ((dataGrid[x][y] == players[0].getPlayerSign()) || (dataGrid[x][y] == players[1].getPlayerSign())) {
                    cout << "Cell is already taken, please select another one" << endl;
                    continue;
                }

                if ((x >= 0 && x<=2) && (y >= 0 && y<=2))  {
                    break;
                }
               
                cout << "Wrong input, please select from cells [0,0] to [2,2]" << endl;
            }

            dataGrid[x][y] = players[0].getPlayerSign();
        };

        bool isGameOver() {
            bool isGameOver = false;

            // Retrieve players information

            for (const auto& player : players) {
                string playerName = player.getPlayerName();
                string sign = player.getPlayerSign();

                int sum;
                for (int i = 0; i < 3; i++) {
                    sum = 0;
                    for (int j = 0; j < 3; j++) {
                        if (dataGrid[i][j] == sign) {
                            sum++;
                        }
                    }

                    if (sum == 3) {
                        isGameOver = true;
                    }
                }

                for (int j = 0; j < 3; j++) {
                    sum = 0;
                    for (int i = 0; i < 3; i++) {
                        if (dataGrid[i][j] == sign) {
                            sum++;
                        }
                    }

                    if (sum == 3) {
                        isGameOver = true;
                    }
                }

                // Check first diagonal
                sum = 0;
                for (int i = 0; i < 3; i++) {
                    if (dataGrid[i][i] == sign) {
                        sum++;
                    }
                }

                if (sum == 3) {
                    isGameOver = true;
                }
                
                // Check second diagonal
                sum = 0;
                for (int i = 0; i < 3; i++) {
                    if (dataGrid[2 - i][i] == sign) {
                        sum++;
                    }
                }
                
                if (sum == 3) {
                    isGameOver = true;
                }
            }

            return isGameOver;
        }
};

int main() {

    cout << "Hello, please start your game!" << endl;

    // Declare game
    std::vector<Game> game = Game::createGame();

    // Start the game
    // while (true) {

    // }
    
    return 0;
};