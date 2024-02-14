#pragma once

#include <conio.h>
#include <Windows.h>

#include <cctype>

#include <algorithm>
#include <vector>
#include <string>
#include <array>
#include <random>
#include <memory>
#include <stdexcept>
#include <print>

class SnakeGame final
{
public:
    SnakeGame() = delete;

    SnakeGame(std::pair<int, int> dimensions)
        :
        dimensions_{ dimensions.first, dimensions.second }
    {

    }


public:
    void Play()
    {
        game_board_ = new Board(dimensions_);

        game_board_->Draw();

        do
        {
            do
            {
                move_ = tolower((int)_getch());
            }
            while ((move_ == left_ && lastmove_ == right_) || (move_ == right_ && lastmove_ == left_) || (move_ == up_ && lastmove_ == down_) || (move_ == down_ && lastmove_ == up_));

            if (move_ == end_)
            {
                game_board_->Draw();

                break;
            }

            lastmove_ = move_;

            if (move_ == up_ || move_ == down_ || move_ == left_ || move_ == right_)
            {
                game_board_->MakeMove(move_, score_, gameover_, hitapple_);
                game_board_->Draw();
            }
        }
        while (! gameover_ && move_ != won_);

        std::println("\n\nGame {0}!\n{1}", move_ == end_ ? "Terminated" : (move_ == won_ ? "Ended" : "Over"), credits_);

        delete game_board_;
    }


protected:


private:
    struct Pos
    {
        int x;
        int y;
    };

    class Board
    {
        friend class SnakeGame;

    public:
        Board(Pos dimensions)
            :
            mrnd_(std::random_device{}()),
            dimensions_{ dimensions.x, dimensions.y }
        {
            board_.reserve(dimensions.x);

            for (size_t i = 0u; i < dimensions.x; ++i)
            {
                board_.emplace_back(dimensions.y, 0);
            }

            // Placing snake's head_ 'X'
            board_[0][1] = 1;

            // Placing snake's first 'O'
            board_[0][0] = 2;

            PlaceApple_();
        }

    public:
        void Draw() const
        {
            std::system("CLS");

            for (int i = 0; i < dimensions_.x + 2; i++)
            {
                for (int j = 0; j < dimensions_.y + 2; j++)
                {
                    if (i == 0 || j == 0 || i == dimensions_.x + 1 || j == dimensions_.y + 1)
                    {
                        std::print("#");
                    }
                    else
                    {
                        switch (board_[i - 1][j - 1])
                        {
                        case -1:
                        {
                            std::print("*");
                            break;
                        }

                        case 0:
                        {
                            std::print(" ");
                            break;
                        }

                        case 1:
                        {
                            std::print("X");
                            break;
                        }

                        default:
                        {
                            std::print("O");
                            break;
                        }
                        }
                    }
                }

                std::print("\n");
            }
        }
        void MakeMove(char& move, int& score, bool& gameover, bool& hitapple)
        {
            FindAndSetHeadLocation_();

            if ((move == SnakeGame::up_ && board_[(head_.x - 1 + dimensions_.x) % dimensions_.x][head_.y] > 1) ||
                (move == SnakeGame::down_ && board_[(head_.x + 1) % dimensions_.x][head_.y] > 1) ||
                (move == SnakeGame::left_ && board_[head_.x][(head_.y - 1 + dimensions_.y) % dimensions_.y] > 1) ||
                (move == SnakeGame::right_ && board_[head_.x][(head_.y + 1) % dimensions_.y] > 1))
            {
                gameover = true;

                return;
            }

            MoveBoard_(move, score, hitapple);
        }

    protected:

    private:
        Board() = default;

    private:
        void IncreaseNumbers_()
        {
            for (int i = 0; i < dimensions_.x; i++)
            {
                for (int j = 0; j < dimensions_.y; j++)
                {
                    if (board_[i][j] > 1)
                    {
                        board_[i][j]++;
                    }
                }
            }
        }
        void FindAndSetHeadLocation_()
        {
            for (int i = 0; i < dimensions_.x; i++)
            {
                for (int j = 0; j < dimensions_.y; j++)
                {
                    if (board_[i][j] == 1)
                    {
                        head_.x = i;
                        head_.y = j;

                        return;
                    }
                }
            }
        }
        void FindAndSetTailLocation_()
        {
            int greatest = 0;

            for (int i = 0; i < dimensions_.x; i++)
            {
                for (int j = 0; j < dimensions_.y; j++)
                {
                    if (board_[i][j] > greatest)
                    {
                        tail_.x = i;
                        tail_.y = j;

                        greatest = board_[i][j];
                    }
                }
            }
        }
        void PlaceApple_()
        {
            do
            {
                apple_.x = mrnd_() % dimensions_.x;
                apple_.y = mrnd_() % dimensions_.y;
            }
            while (board_[apple_.x][apple_.y] > 0);

            board_[apple_.x][apple_.y] = -1;
        }
        void SwapHeadAndTail_(const char& move)
        {
            switch (move)
            {
            case SnakeGame::up_:
            {
                std::swap(board_[head_.x][head_.y], board_[head_.x == 0 ? dimensions_.x - 1 : head_.x - 1][head_.y]);
                break;
            }
            case SnakeGame::down_: 
            {
                std::swap(board_[head_.x][head_.y], board_[head_.x == dimensions_.x - 1 ? 0 : head_.x + 1][head_.y]);
                break;
            }
            case SnakeGame::left_: 
            {
                std::swap(board_[head_.x][head_.y], board_[head_.x][head_.y == 0 ? dimensions_.y - 1 : head_.y - 1]);
                break;
            }
            case SnakeGame::right_:
            {
                std::swap(board_[head_.x][head_.y], board_[head_.x][head_.y == dimensions_.y - 1 ? 0 : head_.y + 1]);
                break;
            }
            default: break;
            }
        }
        void MoveBoard_(char& move, int& score, bool& hitapple)
        {
            if ((move == SnakeGame::up_ && board_[(head_.x - 1 + dimensions_.x) % dimensions_.x][head_.y] == -1) ||
                (move == SnakeGame::down_ && board_[(head_.x + 1) % dimensions_.x][head_.y] == -1) ||
                (move == SnakeGame::left_ && board_[head_.x][(head_.y - 1 + dimensions_.y) % dimensions_.y] == -1) ||
                (move == SnakeGame::right_ && board_[head_.x][(head_.y + 1) % dimensions_.y] == -1))
            {
                hitapple = true;

                score++;

                board_[apple_.x][apple_.y] = 1;
                board_[head_.x][head_.y] = 0;

                IncreaseNumbers_();

                board_[head_.x][head_.y] = 2;

                if (score != (dimensions_.x * dimensions_.y - 2))
                {
                    PlaceApple_();
                }
                else
                {
                    move = won_;
                }

                hitapple = ! hitapple;

                return;
            }

            SwapHeadAndTail_(move);
            FindAndSetTailLocation_();
            IncreaseNumbers_();

            board_[head_.x][head_.y] = 2;
            board_[tail_.x][tail_.y] = 0;
        }

    private:
        std::vector<std::vector<int>> board_;

        std::minstd_rand mrnd_;

        Pos head_;
        Pos tail_;
        Pos apple_;

        Pos dimensions_;
    };


private:
    Board* game_board_ = nullptr;

    Pos dimensions_;

    int score_ = 0;

    bool hitapple_ = false;
    bool gameover_ = false;

    static constexpr const char up_ = 'w';
    static constexpr const char left_ = 'a';
    static constexpr const char down_ = 's';
    static constexpr const char right_ = 'd';

    static constexpr const char won_ = 'n';
    static constexpr const char end_ = 0x1b;

    char move_ = right_;
    char lastmove_ = right_;

    static constexpr const std::array<const char* const, 7> error_codes_ =
    {
        "You need to start the game with parameter(s)!\n", // 0x0
        "Too many parameters!\n",                          // 0x1
        "Syntax error on 1st parameter!\n",                // 0x2
        "Syntax error on 2nd parameter!\n",                // 0x3
        "Syntax error on both parameters!\n",              // 0x4
        "Board_ is too small!\n",                           // 0x5
        "Out of memory!\n"                                 // 0x6
    };
    static constexpr const char* const credits_ = "Programmed by fatpound (2022-2023)";
};