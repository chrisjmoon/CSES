// Write your solution here
// C++26 using GCC 16.2
// Debug with std::cerr or std::clog.
// !!! IMPORTANT !!!
// 99% of headers are pre-compiled for you server-side.
// If your submission fails to compile due to a missing header, add it to your submission.

#include <bits/stdc++.h>

class ScoreBoard
{
  public:
    void submitScore(long long ticketId, std::string game, long long score)
    {
        // Record one new submission tagged with ticketId on the given game.
        id_to_state[ticketId] = true;

        if (!name_to_pq.contains(game))
        {
            name_to_pq[game] = pqll{};
        }
        pqll &pq{name_to_pq[game]};

        pq.push(std::pair<long long, long long>{score, ticketId});
    }

    void revokeScore(long long ticketId)
    {
        // Remove the submission with ticketId, if one is live.

        if (id_to_state.contains(ticketId))
        {
            id_to_state[ticketId] = false;
        }
    }

    std::optional<long long> topScore(std::string game)
    {
        // Return the highest live score on the game, or none if there are none.

        if (!name_to_pq.contains(game))
        {
            return std::nullopt;
        }

        pqll pq{name_to_pq[game]};
        while (pq.size())
        {
            auto score_and_id{pq.top()};
            long long id{score_and_id.second};
            if (id_to_state.contains(id) && !id_to_state[id])
            {
                pq.pop();
            }
            else
            {
                return std::optional<long long>{score_and_id.first};
            }
        }

        return std::nullopt;
    }

  private:
    using pqll = std::priority_queue<std::pair<long long, long long>>;

    // maps the game name to the priority queue of scores
    std::unordered_map<std::string, pqll> name_to_pq;

    // maps the ticketId to the valid state
    std::unordered_map<long long, long long> id_to_state;
};

int main()
{
    ScoreBoard board;
    board.submitScore(1, "Pac", 100);
    board.submitScore(2, "Pac", 250);

    // Use Case 1: the highest live score on Pac is 250
    // Output: 250

    std::cout << board.topScore("Pac").value() << "\n";

    std::string = 'c' + "123";
}