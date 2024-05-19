#include <iostream>
#include <vector>
#include <string>

using namespace std;

class PlayerInfo {
private:
    std::string playerName;
    std::string playerSign;

public:
    // Constructor to initialize values
    PlayerInfo(const std::string& name, const std::string& sign)
        : playerName(name), playerSign(sign) {}

    // Getter functions
    std::string getPlayerName() const { return playerName; }
    std::string getPlayerSign() const { return playerSign; }

    // Function to display the players' information
    void displayPlayerInfo() const {
        std::cout << "Player: " << playerName << " - plays with sign: " << playerSign << std::endl;
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
    // Constructor to initialize players and dataGrid
    Game(const std::vector<PlayerInfo>& players)
        : players(players) {
        // Initialize the game with an empty grid of strings
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                dataGrid[i][j] = "-";
            }
        }
    }

    static Game createGame() {
        // Initialize players' information
        std::vector<PlayerInfo> players = PlayerInfo::createPlayers();

        // Create a game instance with the list of players
        return Game(players);
    }

    // Function to print the grid
    void displayGrid() const {
        cout << "+-----------+" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "| ";
            for (int j = 0; j < 3; j++) {
                cout << dataGrid[i][j] << " | ";
            }
            cout << endl;
            if (i < 2) {
                cout << "|---|---|---|" << endl;
            }
        }
        cout << "+-----------+" << endl;
    }

    // Function to handle a player's move
    void playerMove(const PlayerInfo& player) {
        cout << "Player: " << player.getPlayerName() << " enter cell (row and column): " << endl;

        int x, y;
        while (true) {
            cin >> x >> y;

            if ((x < 0 || x > 2) || (y < 0 || y > 2)) {
                cout << "Wrong input, please select from cells [0,0] to [2,2]" << endl;
                continue;
            }

            if ((dataGrid[x][y] == players[0].getPlayerSign()) || (dataGrid[x][y] == players[1].getPlayerSign())) {
                cout << "Cell is already taken, please select another one" << endl;
                continue;
            }

            break;
        }

        dataGrid[x][y] = player.getPlayerSign();
    }

    // Function to check if the game is over
    bool isGameOver() {
        for (const auto& player : players) {
            std::string sign = player.getPlayerSign();

            // Check rows and columns
            for (int i = 0; i < 3; i++) {
                if ((dataGrid[i][0] == sign && dataGrid[i][1] == sign && dataGrid[i][2] == sign) ||
                    (dataGrid[0][i] == sign && dataGrid[1][i] == sign && dataGrid[2][i] == sign)) {
                    return true;
                }
            }

            // Check diagonals
            if ((dataGrid[0][0] == sign && dataGrid[1][1] == sign && dataGrid[2][2] == sign) ||
                (dataGrid[0][2] == sign && dataGrid[1][1] == sign && dataGrid[2][0] == sign)) {
                return true;
            }
        }

        return false;
    }

    // Function to get the list of players
    const std::vector<PlayerInfo>& getPlayers() const {
        return players;
    }
};

int main() {
    cout << "Hello, please start your game!" << endl;

    // Declare and create the game
    Game game = Game::createGame();

    // Main game loop
    int moveCount = 0;
    while (true) {
        game.displayGrid();

        // Players take turns
        game.playerMove(game.getPlayers()[moveCount % 2]);
        moveCount++;

        if (game.isGameOver()) {
            cout << "Game over!" << endl;
            cout << "Player: " << game.getPlayers()[(moveCount - 1) % 2].getPlayerName() << " wins!" << endl;
            break;
        }

        if (moveCount == 9) {
            cout << "It's a draw!" << endl;
            break;
        }
    }

    game.displayGrid();
    return 0;
}
