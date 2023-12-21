#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include<fstream>
#include<chrono>
#include<cstdlib>

/// FUNCTION TO CENTER TEXT ///

void setText(sf::Text &text, float x, float y)
{
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

/// FUNCTION TO READ CONFIG.CFG FILE ///
void readFile(int &columns, int &rows, int& mines)
{
    fstream file("config.cfg");
    if(!file.is_open())
    {
        cout<<"File could not be open" << endl;
    }
    file >> columns >> rows >> mines;
}

/// FUNCTION TO READ LEADERBOARD.TXT FILE ///
void readLeaderboard(std::vector<std::tuple<int, std::string, std::string>>& leaderboard)
{
    std::ifstream file("leaderboard.txt");

    if (!file.is_open())
    {
        std::cout << "File could not be open" << std::endl;
        return;
    }

    int rank;
    std::string line;
    while (std::getline(file, line))
    {
        int firstComma = line.find(',');
        int secondComma = line.find(',', firstComma + 1);

        if (firstComma != std::string::npos && secondComma != std::string::npos)
        {
            std::string rankStr = line.substr(0, firstComma);
            std::string time = line.substr(firstComma + 1, secondComma - firstComma - 1);
            std::string playerName = line.substr(secondComma + 1);

            try
            {
                rank = std::stoi(rankStr);
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error converting rank to integer: " << e.what() << std::endl;
                rank = -1;
            }

            leaderboard.push_back(std::make_tuple(rank, time, playerName));
        }
    }

    file.close();
}

void drawMines(sf::RenderWindow& window, const std::vector<sf::Vector2i>& minePositions, sf::Sprite& minesSprite) {
    for (int i = 0; i < minePositions.size(); i++)
    {
        sf::Vector2i mPosition = minePositions[i];
        minesSprite.setPosition(mPosition.x * 32, mPosition.y * 32);
        window.draw(minesSprite);
    }
}
void drawMinestiles(sf::RenderWindow& window, const std::vector<sf::Vector2i>& minePositions, sf::Sprite& revealedTilesSprite) {
    for (int i = 0; i < minePositions.size(); i++)
    {
        sf::Vector2i mPosition = minePositions[i];
        revealedTilesSprite.setPosition(mPosition.x * 32, mPosition.y * 32);
        window.draw(revealedTilesSprite);
    }
}

void displayLeaderboard(sf::RenderWindow& window, int width_lb, int height_lb, const std::vector<std::tuple<int, std::string, std::string>>& leaderBoard, int& columns, int& rows, sf::Sprite& revealedTilesSprite, sf::Text& text4, sf::Text& text5, bool& gamePaused, std::chrono::high_resolution_clock::time_point& start_time, std::chrono::high_resolution_clock::time_point& start_time2)
{
    sf::RenderWindow window3(sf::VideoMode(width_lb, height_lb), "Minesweeper");
    sf::Event event3;

    /// CREATE REVEALED TILES ///
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            revealedTilesSprite.setPosition(i * 32, j * 32);
            window.draw(revealedTilesSprite);
        }
    }

    window.display();
    window3.clear(sf::Color::Blue);
    window3.draw(text4);

    /// CREATE AN EMPTY STRING ///
    std::string leaderboardText;

    /// ITERATE IN THE VECTOR ///
    for (int i = 0; i < leaderBoard.size(); ++i) {
        const std::tuple<int, std::string, std::string>& entry = leaderBoard[i];
        int rank = std::get<0>(entry);
        std::string time = std::get<1>(entry);
        std::string playerName = std::get<2>(entry);

        std::string displayText = std::to_string(rank) + "\t" + time + "\t" + playerName;

        leaderboardText += displayText;

        if (i < leaderBoard.size() - 1) {
            leaderboardText += "\n\n";
        }
        std::cout << rank;
        std::cout << time;
        std::cout << playerName;
    }

    /// SET GAME AS PAUSED ///
    gamePaused = true;

    /// RESUME THE CLOCK ///
    start_time = std::chrono::high_resolution_clock::now();
    start_time2 = std::chrono::high_resolution_clock::now();

    /// WINDOW DISPLAY ///
    text5.setString(leaderboardText);
    setText(text5, (width_lb / 2.0f), (height_lb / 2.0f) + 20);
    window3.draw(text5);
    window3.display();

    while (window3.isOpen()) {
        while (window3.pollEvent(event3)) {
            if (event3.type == sf::Event::Closed) {
                window3.close();
            }
        }
    }
}

void displayLeaderboard2(sf::RenderWindow& window, int width_lb, int height_lb, const std::vector<std::tuple<int, std::string, std::string>>& leaderBoard, int& columns, int& rows, sf::Sprite& revealedTilesSprite, sf::Text& text4, sf::Text& text5, bool& gamePaused, std::chrono::high_resolution_clock::time_point& start_time, std::chrono::high_resolution_clock::time_point& start_time2)
{
    sf::RenderWindow window3(sf::VideoMode(width_lb, height_lb), "Minesweeper");
    sf::Event event3;

    window.display();
    window3.clear(sf::Color::Blue);
    window3.draw(text4);



    /// CREATE AN EMPTY STRING ///
    std::string leaderboardText;

    /// ITERATE IN THE VECTOR ///
    for (int i = 0; i < leaderBoard.size(); ++i) {
        const std::tuple<int, std::string, std::string>& entry = leaderBoard[i];
        int rank = std::get<0>(entry);
        std::string time = std::get<1>(entry);
        std::string playerName = std::get<2>(entry);

        std::string displayText = std::to_string(rank) + "\t" + time + "\t" + playerName;

        leaderboardText += displayText;

        if (i < leaderBoard.size() - 1)
        {
            leaderboardText += "\n\n";
        }
        std::cout << rank;
        std::cout << time;
        std::cout << playerName;
    }

    /// SET GAME AS PAUSED ///
    gamePaused = true;

    /// RESUME THE CLOCK ///
    start_time = std::chrono::high_resolution_clock::now();
    start_time2 = std::chrono::high_resolution_clock::now();

    /// WINDOW DISPLAY ///
    text5.setString(leaderboardText);
    setText(text5, (width_lb / 2.0f), (height_lb / 2.0f) + 20);
    window3.draw(text5);
    window3.display();

    while (window3.isOpen()) {
        while (window3.pollEvent(event3)) {
            if (event3.type == sf::Event::Closed) {
                window3.close();

            }
            break;
        }
    }
}
int main()
{
    int columns, rows, mines;
    readFile(columns, rows, mines);
    int width = columns * 32;
    int height = (rows * 32) + 100;
    int width_lb = columns * 16;
    int height_lb = (rows * 16) + 50;
    std::vector<std::tuple<int, std::string, std::string>> leaderBoard;

    readLeaderboard(leaderBoard);

    /// CLASS FOR TILE STATES ///
    enum class TileState{
        Hidden,
        Revealed,
        Mine,
        Flagged,
    };

    /// VECTOR FOR TILES ///
    std::vector<std::vector<TileState>> tileStates(columns, std::vector<TileState>(rows, TileState::Hidden));

    /// VECTOR FOR TILE NUMBERS ///
    std::vector<std::vector<int>> tileNumbers(columns, std::vector<int>(rows, 0));

    /// CHECK IF THE FONT IS BEING READ ///
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        std::cout << "Error" << std::endl;
        return 0;
    }

    /// CREATE THE TITLE FOR WELCOME WINDOW AND SET IT ///
    sf::Text text;
    text.setString("WELCOME TO MINESWEEPER!");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setFillColor(sf::Color::White);
    setText(text,width/2.0f, height/2.0f - 150);

    /// CREATE SECOND TITLE FOR WELCOME WINDOW AND SET IT ///
    sf::Text text2;
    text2.setString("Enter your name:");
    text2.setFont(font);
    text2.setCharacterSize(20);
    text2.setStyle(sf::Text::Bold);
    text2.setFillColor(sf::Color::White);
    setText(text2,width/2.0f, height/2.0f - 75); /// SET TEXT TO CENTER ///

    /// CREATE INPUT TEXT FOR WELCOME WINDOW ///
    std::string playerName;
    sf::Text text3;
    text3.setFont(font);
    text3.setString("|");
    text3.setCharacterSize(18);
    text3.setFillColor(sf::Color::Yellow);
    text3.setStyle(sf::Text::Bold);

    /// CREATE TITLE FOR LEADERBOARD WINDOW ///
    sf::Text text4;
    text4.setString("LEADERBOARD");
    text4.setFont(font);
    text4.setCharacterSize(20);
    text4.setFillColor(sf::Color::White);
    text4.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(text4, width_lb/2.0f,(height_lb/2.0f) - 120);

    sf::Text text5;
    text5.setFont(font);
    text5.setCharacterSize(18);
    text5.setStyle(sf::Text::Bold);
    text5.setFillColor(sf::Color::White);

    /// CREATE A BOOL FOR FIRST LETTER, THIS IS USED FOR THE UPPERCASE LETTER IN THE NAME ///
    bool firstChar = true;

    /// CREATE SPRITE FOR HIDDEN TAILS ///
    sf::Texture tileTexture = TextureManager::getTexture("tile_hidden");
    sf::Sprite tileSprite;
    tileSprite.setTexture(tileTexture);

    /// CREATE SPRITE FOR HAPPY FACE BUTTON ///
    sf::Texture happyTexture = TextureManager::getTexture("face_happy");
    sf::Sprite happySprite;
    happySprite.setTexture(happyTexture);
    happySprite.setPosition(((columns / 2.0f) * 32) - 32, 32 * (rows + 0.5f));

    /// CREATE SPRITE FOR FACE LOSE ///
    sf::Texture faceLoseTexture = TextureManager::getTexture("face_lose");
    sf::Sprite faceLoseSprite;
    faceLoseSprite.setTexture(faceLoseTexture);
    faceLoseSprite.setPosition(((columns / 2.0f) * 32) - 32, 32 * (rows + 0.5f));

    /// CREATE SPRITE FOR DEBUG BUTTON ///
    sf::Texture debugTexture = TextureManager::getTexture("debug");
    sf::Sprite debugSprite;
    debugSprite.setTexture(debugTexture);
    debugSprite.setPosition((columns * 32) - 304, 32 * (rows + 0.5f));

    /// CREATE SPRITE FOR PLAY BUTTON ///
    sf::Texture playTexture = TextureManager::getTexture("play");
    sf::Sprite playSprite;
    playSprite.setTexture(playTexture);
    playSprite.setPosition((columns * 32) - 240, 32 * (rows + 0.5f));

    /// CREATE SPRITE FOR PAUSE BUTTON ///
    sf::Texture pauseTexture = TextureManager::getTexture("pause");
    sf::Sprite pauseSprite;
    pauseSprite.setTexture(pauseTexture);
    pauseSprite.setPosition((columns * 32) - 240, 32 * (rows + 0.5f));

    /// CREATE A SPRITE FOR LEADERBOARD ///
    sf::Texture lbTexture = TextureManager::getTexture("leaderboard");
    sf::Sprite lbSprite;
    lbSprite.setTexture(lbTexture);
    lbSprite.setPosition((columns * 32) - 176, 32 * (rows + 0.5f));

    /// CREATE A SPRITE FOR MINUTES ///
    sf::Texture& minutesTexture = TextureManager::getTexture("digits");
    sf::Sprite minutesSprite;
    minutesSprite.setTexture(minutesTexture);
    int digit = 0;
    minutesSprite.setTextureRect(sf::IntRect(digit * 21, 0, 21, 32));
    minutesSprite.setPosition((columns * 32) -97, 32 * (rows + 0.5f) + 16);

    sf::Sprite minutesSprite2;
    minutesSprite2.setTexture(minutesTexture);
    int digit2 = 0;
    minutesSprite2.setTextureRect(sf::IntRect(digit2 * 21, 0, 21, 32));
    minutesSprite2.setPosition((columns * 32) -76, 32 * (rows + 0.5f) + 16);

    /// CREATE A SPRITE FOR SECONDS ///
    sf::Texture secondsTexture = TextureManager::getTexture("digits");
    sf::Sprite secondsSprite;
    int digit3 = 0;
    secondsSprite.setTexture(secondsTexture);
    secondsSprite.setTextureRect(sf::IntRect(digit3 * 21, 0, 21, 32));
    secondsSprite.setPosition((columns * 32) -54, 32 * (rows + 0.5f) + 16);

    sf::Sprite secondsSprite2;
    secondsSprite2.setTexture(secondsTexture);
    int digit4 = 0;
    secondsSprite2.setTextureRect(sf::IntRect(digit4 * 21, 0, 21, 32));
    secondsSprite2.setPosition((columns * 32) -33, 32 * (rows + 0.5f) + 16);

    /// CREATE SPRITES FOR MINE COUNT ///
    sf::Texture mcTexture = TextureManager::getTexture("digits");
    sf::Sprite mcSprite;
    mcSprite.setTexture(mcTexture);
    int digit5 = (mines / 100) % 10;
    mcSprite.setTextureRect(sf::IntRect(digit5 * 21, 0, 21, 32));
    mcSprite.setPosition((33), 32 * (rows + 0.5) + 16);

    sf::Sprite mcSprite2;
    mcSprite2.setTexture(mcTexture);
    int digit6 = (mines / 10) % 10;
    mcSprite2.setTextureRect(sf::IntRect(digit6 * 21, 0, 21, 32));
    mcSprite2.setPosition((53), 32 * (rows + 0.5) + 16);

    sf::Sprite mcSprite3;
    mcSprite3.setTexture(mcTexture);
    int digit7 = mines % 10 ;
    mcSprite3.setTextureRect(sf::IntRect(digit7 * 21, 0, 21, 32));
    mcSprite3.setPosition((74), 32 * (rows + 0.5) + 16);

    /// CREATE A SPRITE FOR REVEALED TILES ///
    sf::Texture revealedTilesTexture = TextureManager::getTexture("tile_revealed");
    sf::Sprite revealedTilesSprite;
    revealedTilesSprite.setTexture(revealedTilesTexture);

    /// CREATE A SPRITE FOR THE MINES ///
    sf::Texture& minesTexture = TextureManager::getTexture("mine");
    sf::Sprite minesSprite;
    minesSprite.setTexture(minesTexture);

    /// CREATE A SPRITE FOR THE FLAG ///
    sf::Texture flagTexture = TextureManager::getTexture("flag");
    sf::Sprite flagSprite;
    flagSprite.setTexture(flagTexture);

    /// CREATE A SPRITE FOR NUMBER 1 ///
    sf::Texture number1Texture = TextureManager::getTexture("number_1");
    sf::Sprite number1Sprite;
    number1Sprite.setTexture(number1Texture);

    /// CREATE A SPRITE FOR NUMBER 2 ///
    sf::Texture number2Texture = TextureManager::getTexture("number_2");
    sf::Sprite number2Sprite;
    number2Sprite.setTexture(number2Texture);

    /// CREATE A SPRITE FOR NUMBER 3 ///
    sf::Texture number3Texture = TextureManager::getTexture("number_3");
    sf::Sprite number3Sprite;
    number3Sprite.setTexture(number3Texture);

    /// CREATE A SPRITE FOR NUMBER 4 ///
    sf::Texture number4Texture = TextureManager::getTexture("number_4");
    sf::Sprite number4Sprite;
    number4Sprite.setTexture(number4Texture);

    /// CREATE A SPRITE FOR NUMBER 5 ///
    sf::Texture number5Texture = TextureManager::getTexture("number_5");
    sf::Sprite number5Sprite;
    number5Sprite.setTexture(number5Texture);

    /// CREATE A SPRITE FOR NUMBER 6 ///
    sf::Texture number6Texture = TextureManager::getTexture("number_6");
    sf::Sprite number6Sprite;
    number6Sprite.setTexture(number6Texture);

    /// CREATE A SPRITE FOR NUMBER 7 ///
    sf::Texture number7Texture = TextureManager::getTexture("number_7");
    sf::Sprite number7Sprite;
    number7Sprite.setTexture(number7Texture);

    /// CREATE A SPRITE FOR NUMBER 8 ///
    sf::Texture number8Texture = TextureManager::getTexture("number_8");
    sf::Sprite number8Sprite;
    number8Sprite.setTexture(number8Texture);

    /// CREATE A SPRITE FOR FACE WIN ///
    sf::Texture faceWinTexture = TextureManager::getTexture("face_win");
    sf::Sprite faceWinSprite;
    faceWinSprite.setTexture(faceWinTexture);
    faceWinSprite.setPosition(((columns / 2.0f) * 32) - 32, 32 * (rows + 0.5f));

    /// CREATE WELCOME WINDOW ///
    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper");

    /// WELCOME WINDOW IS OPEN ///
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    char someChar = static_cast<char>(event.text.unicode);

                    /// CHECK IF TEXT HAS ALPHABET LETTERS AND DO NOT EXCEED MORE THAN 10 CHARACTERS ///
                    if ((std::isalpha(someChar)) && playerName.length() < 10)
                    {
                        /// SET FIRST LETTER TO UPPERCASE ///
                        if(firstChar)
                        {
                            playerName += std::toupper(someChar);
                            firstChar = false;
                        }
                        else
                        {
                            playerName +=std::tolower(someChar);
                        }
                        text3.setString(playerName + sf::String("|"));
                        setText(text3, width/2.0f, height/2.0f - 45);
                    }
                }
            }
            /// IF A KEYBOARD IS PRESSED ///
            else if (event.type == sf::Event::KeyPressed)
            {
                /// BACKSPACE ///
                if (event.key.code == sf::Keyboard::Backspace)
                {
                    if (!playerName.empty())
                    {
                        playerName.pop_back();
                        text3.setString(playerName + sf::String("|"));
                        setText(text3,width/2.0f, height/2.0f - 45);

                    }
                }
                /// ENTER ///
                else if (event.key.code == sf::Keyboard::Enter)
                {
                    if(!playerName.empty())
                    {
                        window.close();


                        /// IF ENTER IS PRESSED, GAME WINDOW IS OPEN ///
                        sf::RenderWindow window2(sf::VideoMode(width, height), "Minesweeper");

                        /// BUTTON FOR PAUSE ///
                        bool pauseButton_Visible = false;

                        /// BUTTON FOR DEBUG ///
                        bool debugButton = false;

                        /// BUTTON FOR HAPPY FACE ///
                        bool happyFace = false;

                        /// BUTTON FOR LEADERBOARD ///
                        bool leaderboard = false;

                        /// BOOL FOR PAUSED GAME ///
                        bool gamePaused = false;

                        /// BOOL FOR GAME LOSE ///
                        bool gameLose = false;

                        /// BOOL FOR GAME WIN ///
                        bool gameWin = false;

                        /// BOOL FOR GAME RESET ///
                        bool gameReset = false;

                        bool lbdisplay = false;

                        /// CREATE THE CLOCK ///
                        auto start_time = std::chrono::high_resolution_clock::now();
                        auto start_time2 = std::chrono::high_resolution_clock::now();

                        /// CREATE VECTOR FOR MINES ///
                        std::vector<sf::Vector2i> minePositions;

                        /// SET MINES TO RANDOM POSITIONS ///
                        minePositions.clear();
                        while (minePositions.size() < mines)
                        {
                            int random1 = rand() % columns;
                            int random2 = rand() % rows;

                            sf::Vector2i position(random1, random2);

                            if (std::find(minePositions.begin(), minePositions.end(), position) == minePositions.end())
                            {
                                minePositions.push_back(position);
                            }
                        }

                        /// SET THE NUMBERS IN TILES ///
                        for (const auto& minePos : minePositions)
                        {
                            for (int j = -1; j <= 1; ++j)
                            {
                                for (int k = -1; k <= 1; ++k)
                                {
                                    int col = minePos.x + j;
                                    int row = minePos.y + k;

                                    if (col >= 0 && col < columns && row >= 0 && row < rows)
                                    {
                                        ++tileNumbers[col][row];
                                    }
                                }
                            }
                        }

                        /// GAME WINDOW IS OPEN ///
                        while(window2.isOpen())
                        {

                            sf::Event event2;
                            while(window2.pollEvent(event2))
                            {
                                /// GAME WINDOW IS CLOSED WHERE CLICK IN X ///
                                if(event2.type == sf::Event::Closed)
                                {
                                    window2.close();
                                }

                                /// WHEN A SPECIFIC BUTTON IS PRESSED ///
                                if(event2.type == sf::Event::MouseButtonPressed)
                                {
                                    if(event2.mouseButton.button == sf::Mouse::Left)
                                    {
                                        sf::Vector2i mouse;
                                        mouse = sf::Mouse::getPosition(window2);

                                        /// CONVERT MOUSE COORDINATES TO GRID COORDINATES ///
                                        int col = mouse.x / 32;
                                        int row = mouse.y / 32;

                                        /// CHECK IF COORDINATES ARE WITHIN A VALID RANGE ///
                                        if (col >= 0 && col < columns && row >= 0 && row < rows)
                                        {
                                            /// WHEN CLICK IN A TILE ///
                                            if (tileStates[col][row] == TileState::Hidden)
                                            {
                                                /// UPDATE THE STATE ///
                                                tileStates[col][row] = TileState::Revealed;
                                                tileSprite.setPosition(col * 32, row * 32);
                                                window2.draw(tileSprite);

                                                /// IF THE REVEALED TILES HAS NO ADJACENT MINES, REVEALED TILES RECURSIVELY ///
                                                if (tileNumbers[col][row] == 0)
                                                {
                                                    for (int i = -1; i <= 1; ++i)
                                                    {
                                                        for (int j = -1; j <= 1; ++j)
                                                        {
                                                            int adjacentCol = col + i;
                                                            int adjacentRow = row + j;

                                                            /// CHECK IF ADJACENT COORDINATES ARE WITHIN A VALID RANGE ///
                                                            if (adjacentCol >= 0 && adjacentCol < columns && adjacentRow >= 0 && adjacentRow < rows)
                                                            {
                                                                /// RECURSIVELY REVEAL ADJACENT TILES ///
                                                                if (tileStates[adjacentCol][adjacentRow] == TileState::Hidden)
                                                                {
                                                                    tileStates[adjacentCol][adjacentRow] = TileState::Revealed;
                                                                    tileSprite.setPosition(adjacentCol * 32, adjacentRow * 32);
                                                                    window2.draw(tileSprite);

                                                                    /// CONTINUE REVEALING IF THE ADJACENT TILE HAS NO ADJACENT MINES ///
                                                                    if (tileNumbers[adjacentCol][adjacentRow] == 0)
                                                                    {
                                                                        for (int m = -1; m <= 1; ++m)
                                                                        {
                                                                            for (int n = -1; n <= 1; ++n)
                                                                            {
                                                                                int adjCol = adjacentCol + m;
                                                                                int adjRow = adjacentRow + n;

                                                                                if (adjCol >= 0 && adjCol < columns && adjRow >= 0 && adjRow < rows)
                                                                                {
                                                                                    if (tileStates[adjCol][adjRow] == TileState::Hidden)
                                                                                    {
                                                                                        tileStates[adjCol][adjRow] = TileState::Revealed;
                                                                                        tileSprite.setPosition(adjCol * 32, adjRow * 32);
                                                                                        window2.draw(tileSprite);
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }

                                        /// WHEN PLAY BUTTON IS PRESSED ///
                                        if(playSprite.getGlobalBounds().contains(window2.mapPixelToCoords(mouse)))
                                        {
                                            pauseButton_Visible = !pauseButton_Visible;
                                            start_time = std::chrono::high_resolution_clock::now();
                                            start_time2 = std::chrono::high_resolution_clock::now();
                                        }

                                        /// WHEN DEBUG BUTTON IS PRESSED ///
                                        if (debugSprite.getGlobalBounds().contains(window2.mapPixelToCoords(mouse)))
                                        {
                                            debugButton = !debugButton;
                                        }

                                        /// WHEN HAPPY SPRITE IS PRESSED ///
                                        if (happySprite.getGlobalBounds().contains(window2.mapPixelToCoords(mouse)))
                                        {
                                            happyFace = !happyFace;
                                            gameReset = true;

                                            /// CLEAR TILE NUMBERS ///
                                            tileNumbers.clear();
                                            tileNumbers.resize(columns, std::vector<int>(rows, 0));

                                            /// RESET THE POSITION OF THE MINES EVERYTIME HAPPY FACE BUTTON IS CLICKED ///
                                            minePositions.clear();
                                            while (minePositions.size() < mines)
                                            {
                                                int random1 = rand() % columns;
                                                int random2 = rand() % rows;

                                                sf::Vector2i position(random1, random2);

                                                if (std::find(minePositions.begin(), minePositions.end(), position) == minePositions.end())
                                                {
                                                    minePositions.push_back(position);
                                                }
                                            }

                                            for (int i = 0; i < minePositions.size(); ++i) {
                                                const auto& minePos = minePositions[i];

                                                for (int j = -1; j <= 1; ++j) {
                                                    for (int k = -1; k <= 1; ++k) {
                                                        int col = minePos.x + j;
                                                        int row = minePos.y + k;

                                                        if (col >= 0 && col < columns && row >= 0 && row < rows && tileStates[col][row] != TileState::Mine) {
                                                            ++tileNumbers[col][row];
                                                        }
                                                    }
                                                }
                                            }

                                            /// RESET THE BUTTON TO PLAY BOTTOM ///
                                            pauseButton_Visible = false;

                                            /// RESET THE CLOCK VALUES TO 0, SO WHEN PLAY BUTTON IS CLICKED AGAIN,
                                            /// THE CLOCK RESTART FROM THE BEGINNING ///

                                            digit3 = 0;
                                            digit4 = 0;
                                            secondsSprite2.setTextureRect(sf::IntRect(digit4 * 21, 0, 21, 32));
                                            secondsSprite.setTextureRect(sf::IntRect(digit3 * 21, 0, 21, 32));

                                            digit = 0;
                                            digit2 = 0;
                                            minutesSprite2.setTextureRect(sf::IntRect(digit2 * 21, 0, 21, 32));
                                            minutesSprite.setTextureRect(sf::IntRect(digit * 21, 0, 21, 32));

                                            /// RESET THE TILES ///
                                            for (int i = 0; i < columns; i++)
                                            {
                                                for (int j = 0; j < rows; j++)
                                                {
                                                    tileStates[i][j] = TileState::Hidden;
                                                    tileSprite.setPosition(i * 32, j * 32);
                                                    window2.draw(tileSprite);
                                                }
                                            }
                                            gameLose = false;
                                            gameWin = false;
                                            window.draw(happySprite);
                                            debugButton = false;
                                        }

                                        /// WHEN LEADERBOARD BUTTON IS PRESSED ///
                                        if (lbSprite.getGlobalBounds().contains(window2.mapPixelToCoords(mouse)))
                                        {
                                            displayLeaderboard(window2, width_lb, height_lb, leaderBoard, columns, rows, revealedTilesSprite, text4, text5, gamePaused, start_time, start_time2);
                                            /// RESUME THE CLOCK ///
                                            start_time = std::chrono::high_resolution_clock::now();
                                            start_time2 = std::chrono::high_resolution_clock::now();
                                        }
                                    }

                                    if(event2.mouseButton.button == sf::Mouse::Right)
                                    {
                                        sf::Vector2i mouse;
                                        mouse = sf::Mouse::getPosition(window2);
                                        /// CONVERT MOUSE COORDINATES TO GRID COORDINATES ///
                                        int col = mouse.x / 32;
                                        int row = mouse.y / 32;

                                        /// CHECK IF COORDINATES ARE WITHIN A VALID RANGE ///
                                        if (col >= 0 && col < columns && row >= 0 && row < rows)
                                        {

                                            /// IF TILE IS HIDDEN ///
                                            if (tileStates[col][row] == TileState::Hidden)
                                            {
                                                /// UPDATE THE STATE TO FLAGGED ///
                                                tileStates[col][row] = TileState::Flagged;

                                                /// COUNT DOWN MINE COUNTER WHEN A TILE IS FLAGGED ///
                                                if(digit6 == 5)
                                                {
                                                    digit6 = digit6 - 1;
                                                    mcSprite2.setTextureRect(sf::IntRect(digit6 * 21, 0, 21, 32));
                                                    digit7 = 10;
                                                }
                                                if(digit7 <= 10)
                                                {
                                                    digit7 = digit7-1;
                                                    mcSprite3.setTextureRect(sf::IntRect(digit7 * 21, 0, 21, 32));
                                                }
                                                if(digit6 == 4 && digit7 < 0)
                                                {
                                                    digit6 = digit6 - 1;
                                                    mcSprite2.setTextureRect(sf::IntRect(digit6 * 21, 0, 21, 32));
                                                    digit7 = 9;
                                                    mcSprite3.setTextureRect(sf::IntRect(digit7 * 21, 0, 21, 32));
                                                }
                                                if(digit6 == 3 && digit7 < 0)
                                                {
                                                    digit6 = digit6 - 1;
                                                    mcSprite2.setTextureRect(sf::IntRect(digit6 * 21, 0, 21, 32));
                                                    digit7 = 9;
                                                    mcSprite3.setTextureRect(sf::IntRect(digit7 * 21, 0, 21, 32));
                                                }
                                                if(digit6 == 2 && digit7 < 0)
                                                {
                                                    digit6 = digit6 - 1;
                                                    mcSprite2.setTextureRect(sf::IntRect(digit6 * 21, 0, 21, 32));
                                                    digit7 = 9;
                                                    mcSprite3.setTextureRect(sf::IntRect(digit7 * 21, 0, 21, 32));
                                                }
                                                if(digit6 == 1 && digit7 < 0)
                                                {
                                                    digit6 = digit6 - 1;
                                                    mcSprite2.setTextureRect(sf::IntRect(digit6 * 21, 0, 21, 32));
                                                    digit7 = 9;
                                                    mcSprite3.setTextureRect(sf::IntRect(digit7 * 21, 0, 21, 32));
                                                }
                                            }

                                            /// IF A TILE IS FLAGGED ///
                                            else if(tileStates[col][row] == TileState::Flagged)
                                            {
                                                /// UPDATE TO HIDDEN STATE ///
                                                tileStates[col][row] = TileState::Hidden;

                                                /// COUNTER GOING UP WHEN FLAG IS REMOVED ///
                                                if(digit6 == 5)
                                                {
                                                    digit6 = digit6 +1;
                                                    mcSprite2.setTextureRect(sf::IntRect(digit6 * 21, 0, 21, 32));
                                                    digit7 = 10;
                                                }
                                                if(digit7 <= 10)
                                                {
                                                    digit7 = digit7+1;
                                                    mcSprite3.setTextureRect(sf::IntRect(digit7 * 21, 0, 21, 32));
                                                }
                                                if(digit7 == 10)
                                                {
                                                    digit6 = digit6 + 1;
                                                    mcSprite2.setTextureRect(sf::IntRect(digit6 * 21, 0, 21, 32));
                                                    digit7 = 0;
                                                    mcSprite3.setTextureRect(sf::IntRect(digit7 * 21, 0, 21, 32));
                                                }
                                                if(digit6 == 4 && digit7 < 0)
                                                {
                                                    digit6 = digit6 + 1;
                                                    mcSprite2.setTextureRect(sf::IntRect(digit6 * 21, 0, 21, 32));
                                                    digit7 = 9;
                                                    mcSprite3.setTextureRect(sf::IntRect(digit7 * 21, 0, 21, 32));
                                                }
                                                if(digit6 == 3 && digit7 < 0)
                                                {
                                                    digit6 = digit6 + 1;
                                                    mcSprite2.setTextureRect(sf::IntRect(digit6 * 21, 0, 21, 32));
                                                    digit7 = 9;
                                                    mcSprite3.setTextureRect(sf::IntRect(digit7 * 21, 0, 21, 32));
                                                }
                                                if(digit6 == 2 && digit7 < 0)
                                                {
                                                    digit6 = digit6 + 1;
                                                    mcSprite2.setTextureRect(sf::IntRect(digit6 * 21, 0, 21, 32));
                                                    digit7 = 9;
                                                    mcSprite3.setTextureRect(sf::IntRect(digit7 * 21, 0, 21, 32));
                                                }
                                                if(digit6 == 1 && digit7 < 0)
                                                {
                                                    digit6 = digit6 + 1;
                                                    mcSprite2.setTextureRect(sf::IntRect(digit6 * 21, 0, 21, 32));
                                                    digit7 = 9;
                                                    mcSprite3.setTextureRect(sf::IntRect(digit7 * 21, 0, 21, 32));
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            /// SET THE BACKGROUND COLOR ///
                            window2.clear(sf::Color::White);

                            /// DRAW TILES ///
                            for (int i = 0; i < columns; i++)
                            {
                                for (int j = 0; j < rows; j++)
                                {
                                    /// IF TILE IS REVEALED ///
                                    if (tileStates[i][j] == TileState::Revealed)
                                    {
                                        /// DRAW REVEALED TILE ///
                                        revealedTilesSprite.setPosition(i * 32, j * 32);
                                        window2.draw(revealedTilesSprite);

                                        int number = tileNumbers[i][j];
                                        if (number > 0)
                                        {
                                            switch (number)
                                            {
                                                case 1:
                                                    number1Sprite.setPosition(i * 32, j * 32);
                                                    window2.draw(number1Sprite);
                                                    break;
                                                case 2:
                                                    number2Sprite.setPosition(i * 32, j * 32);
                                                    window2.draw(number2Sprite);
                                                    break;
                                                case 3:
                                                    number3Sprite.setPosition(i * 32, j * 32);
                                                    window2.draw(number3Sprite);
                                                    break;
                                                case 4:
                                                    number4Sprite.setPosition(i * 32, j * 32);
                                                    window2.draw(number4Sprite);
                                                    break;
                                                case 5:
                                                    number5Sprite.setPosition(i * 32, j * 32);
                                                    window2.draw(number5Sprite);
                                                    break;
                                                case 6:
                                                    number6Sprite.setPosition(i * 32, j * 32);
                                                    window2.draw(number6Sprite);
                                                    break;
                                                case 7:
                                                    number7Sprite.setPosition(i * 32, j * 32);
                                                    window2.draw(number7Sprite);
                                                    break;
                                                case 8:
                                                    number3Sprite.setPosition(i * 32, j * 32);
                                                    window2.draw(number8Sprite);
                                                    break;
                                                default:
                                                    break;
                                            }
                                        }
                                    }
                                    /// DRAW FLAGS ///
                                    else if (tileStates[i][j] == TileState::Flagged)
                                    {
                                        /// DRAW HIDDEN TILE BELOW FLAG ///
                                        tileSprite.setPosition(i * 32, j * 32);
                                        window2.draw(tileSprite);

                                        /// DRAW FLAGS ///
                                        flagSprite.setPosition(i * 32, j * 32);
                                        window2.draw(flagSprite);
                                    }
                                    /// DRAW HIDDEN TILES ///
                                    else
                                    {
                                        tileSprite.setPosition(i * 32, j * 32);
                                        window2.draw(tileSprite);
                                    }
                                }
                            }
                            /// LOSE CONDITION - MINES WILL BE REVEALED WHEN PLAYER LOSE THE GAME///
                            for (int i = 0; i < minePositions.size(); i++)
                            {
                                int mineX = minePositions[i].x;
                                int mineY = minePositions[i].y;

                                if (tileStates[mineX][mineY] == TileState::Revealed)
                                {
                                    gameLose = true;
                                    drawMinestiles(window2, minePositions, revealedTilesSprite);
                                    drawMines(window2, minePositions, minesSprite);
                                }
                            }

                            /// WIN CONDITION - FLAGS WILL BE REVEALED AFTER ALL NON MINE TILES ARE REVEALED ///
                            int totalNonMineTiles = columns * rows - mines;
                            int revealedNonMineCount = 0;

                            for (int i = 0; i < columns; i++)
                            {
                                for (int j = 0; j < rows; j++)
                                {
                                    if (tileStates[i][j] == TileState::Revealed)
                                    {
                                        revealedNonMineCount++;
                                    }
                                }
                            }

                            /// WHEN ALL NON MINE TILE ARE REVEALED ///
                            if (revealedNonMineCount == totalNonMineTiles) {
                                /// AUTOMATICALLY SET FLAGS IN MINE POSITIONS WHEN WIN CONDITION IS ACHIEVED ///
                                for (int mineIndex = 0; mineIndex < minePositions.size(); ++mineIndex)
                                {
                                    int mineX = minePositions[mineIndex].x;
                                    int mineY = minePositions[mineIndex].y;
                                    if (tileStates[mineX][mineY] != TileState::Revealed)
                                    {
                                        tileStates[mineX][mineY] = TileState::Flagged;
                                    }
                                }

                                gameWin = true;
                            }

                            /// IF DEBUG BUTTON IS PRESSED, SHOW ALL THE MINES ///
                            if(debugButton)
                            {
                                drawMines(window2, minePositions, minesSprite);
                            }

                            /// SET THE CLOCK ///
                            auto current_time = std::chrono::high_resolution_clock::now();
                            auto duration = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time);
                            auto current_time2 = std::chrono::high_resolution_clock::now();
                            auto duration2 = std::chrono::duration_cast<std::chrono::seconds>(current_time2 - start_time2);

                            /// WHEN PLAY BUTTON IS PRESSED ///
                            if(pauseButton_Visible)
                            {

                                /// SETTINGS FOR SECONDS ///
                                if(duration.count() == 1)
                                {
                                    digit4 = digit4 + 1;
                                    secondsSprite2.setTextureRect(sf::IntRect(digit4  * 21, 0, 21, 32));
                                    start_time = std::chrono::high_resolution_clock::now();
                                }
                                else if(digit4 > 9)
                                {
                                    digit4 = 0;
                                    secondsSprite2.setTextureRect(sf::IntRect(digit4  * 21, 0, 21, 32));
                                    digit3 = digit3 + 1;
                                    secondsSprite.setTextureRect(sf::IntRect(digit3 * 21, 0, 21, 32));
                                }
                                if(digit3 == 5 && digit4 > 9)
                                {
                                    secondsSprite2.setTextureRect(sf::IntRect(digit4  * 21, 0, 21, 32));
                                    digit3 = -1;
                                    secondsSprite.setTextureRect(sf::IntRect(digit3 * 21, 0, 21, 32));
                                }
                                /// SETTINGS FOR MINUTES ///
                                if(duration2.count() == 60)
                                {
                                    digit2 = digit2 + 1;
                                    minutesSprite2.setTextureRect(sf::IntRect(digit2 * 21, 0, 21, 32));
                                    start_time2 = std::chrono::high_resolution_clock::now();
                                }
                                else if(digit2 > 9)
                                {
                                    digit2 = 0;
                                    minutesSprite2.setTextureRect(sf::IntRect(digit2 * 21, 0, 21, 32));
                                    digit = digit + 1;
                                    minutesSprite.setTextureRect(sf::IntRect(digit * 21, 0, 21, 32));
                                }
                                if(digit == 5 && digit2 > 9)
                                {
                                    minutesSprite2.setTextureRect(sf::IntRect(digit2  * 21, 0, 21, 32));
                                    digit = -1;
                                    minutesSprite.setTextureRect(sf::IntRect(digit * 21, 0, 21, 32));
                                }
                            }

                            /// GAME WINDOW SPRITES DISPLAY ///
                            window2.draw(debugSprite);
                            window2.draw(lbSprite);
                            window2.draw(minutesSprite);
                            window2.draw(minutesSprite2);
                            window2.draw(secondsSprite);
                            window2.draw(secondsSprite2);
                            window2.draw(mcSprite);
                            window2.draw(mcSprite2);
                            window2.draw(mcSprite3);
                            if(!pauseButton_Visible)
                            {
                                window2.draw(playSprite);
                            }
                            if(pauseButton_Visible)
                            {
                                window2.draw(pauseSprite);
                            }
                            if(gameLose)
                            {
                                window2.draw(faceLoseSprite);
                                pauseButton_Visible = false;
                            }
                            else
                            {
                                window2.draw(happySprite);
                            }
                            if(gameWin)
                            {

                                window2.draw(faceWinSprite);
                                pauseButton_Visible = false;
                                if(lbdisplay)
                                {
                                    displayLeaderboard2(window2, width_lb, height_lb, leaderBoard, columns, rows,
                                                        revealedTilesSprite, text4, text5, gamePaused, start_time,
                                                        start_time2);
                                    break;

                                }
                                lbdisplay = true;
                            }

                            window2.display();
                        }
                    }
                }
            }
        }
        /// WELCOME WINDOW SPRITES DISPLAY ///
        window.clear(sf::Color::Blue); /// SET THE BACKGROUND COLOR ///
        window.draw(text);
        window.draw(text2);
        window.draw(text3);
        window.display();

    }

    return 0;
}
