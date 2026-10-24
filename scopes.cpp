#include <bits/stdc++.h>
// Write your solution here
// C++26 using GCC 16.2
// Debug with std::cerr or std::clog.
// !!! IMPORTANT !!!
// 99% of headers are pre-compiled for you server-side.
// If your submission fails to compile due to a missing header, add it to your submission.
std::vector<std::string> Parse(std::string_view source)
{
    struct Scope
    {
        std::size_t identifier_index{};
        std::size_t child_count{};
    };

    enum class CommentState
    {
        none,
        line,
        block,
    };

    std::vector<Scope> hierarchy;
    std::vector<std::string> identifiers;

    CommentState comment_state{CommentState::none};
    const std::size_t size{source.size()};
    std::size_t i{};

    while (i < size)
    {
        if (comment_state == CommentState::line)
        {
            if (source[i] == '\n')
            {
                comment_state = CommentState::none;
                i += 1;
            }
            else
            {
                i += 1;
            }
            continue;
        }

        if (comment_state == CommentState::block)
        {
            if (i + 1 < size && source[i] == '*' && source[i + 1] == '/')
            {
                comment_state = CommentState::none;
                i += 2;
            }
            else
            {
                i += 1;
            }
            continue;
        }

        if (source[i] == '/')
        {
            if (i + 1 < size && source[i + 1] == '/')
            {
                comment_state = CommentState::line;
                i += 2;
            }
            else if (i + 1 < size && source[i + 1] == '*')
            {
                comment_state = CommentState::block;
                i += 2;
            }
            else
            {
                i += 1;
            }
            continue;
        }

        if (source[i] == '{')
        {
            if (hierarchy.empty())
            {
                identifiers.emplace_back("1");
            }
            else
            {
                Scope &parent = hierarchy.back();

                std::string identifier = identifiers[parent.identifier_index] + "." +
                                         std::to_string(++parent.child_count);

                identifiers.push_back(std::move(identifier));
            }

            hierarchy.push_back(Scope{identifiers.size() - 1, 0});
        }
        else if (source[i] == '}')
        {
            hierarchy.pop_back();
        }

        i += 1;
    }

    return identifiers;
}

void FoldScopes(std::string &source, const std::vector<std::string> &folding)
{
    struct Scope
    {
        std::size_t identifier_index{};
        std::size_t child_count{};
        std::size_t start_index{};
    };

    enum class CommentState
    {
        none,
        line,
        block,
    };

    std::vector<Scope> hierarchy;
    std::vector<std::string> identifiers;
    std::unordered_set<std::string> fold_scopes{folding.begin(), folding.end()};

    CommentState comment_state{CommentState::none};
    std::size_t i{};

    std::string output{};
    std::optional<std::size_t> fold_start{};
    std::size_t copy_start{};

    while (i < source.size())
    {
        if (comment_state == CommentState::line)
        {
            if (source[i] == '\n')
            {
                comment_state = CommentState::none;
                i += 1;
            }
            else
            {
                i += 1;
            }
            continue;
        }

        if (comment_state == CommentState::block)
        {
            if (i + 1 < source.size() && source[i] == '*' && source[i + 1] == '/')
            {
                comment_state = CommentState::none;
                i += 2;
            }
            else
            {
                i += 1;
            }
            continue;
        }

        if (source[i] == '/')
        {
            if (i + 1 < source.size() && source[i + 1] == '/')
            {
                comment_state = CommentState::line;
                i += 2;
            }
            else if (i + 1 < source.size() && source[i + 1] == '*')
            {
                comment_state = CommentState::block;
                i += 2;
            }
            else
            {
                i += 1;
            }
            continue;
        }

        if (source[i] == '{')
        {
            if (hierarchy.empty())
            {
                identifiers.emplace_back("1");
            }
            else
            {
                Scope &parent = hierarchy.back();

                std::string identifier = identifiers[parent.identifier_index] + "." +
                                         std::to_string(++parent.child_count);

                identifiers.push_back(std::move(identifier));
            }

            if (!fold_start && fold_scopes.contains(identifiers.back()))
            {
                fold_start = i;
            }

            hierarchy.push_back(Scope{identifiers.size() - 1, 0, i});
        }
        else if (source[i] == '}')
        {
            // determine if the identifier is in the fold scope set
            const Scope &scope = hierarchy.back();

            if (fold_start)
            {
                if (scope.start_index == fold_start)
                {
                    // copy everything preceding the fold start
                    // starting from copy start
                    output.append(source, copy_start, scope.start_index - copy_start);
                    output.append("{...}");

                    fold_start.reset();
                    copy_start = i + 1;
                }
            }
            else
            {
                output.append(source, copy_start, i - copy_start + 1);
                copy_start = i + 1;
            }

            hierarchy.pop_back();
        }

        i += 1;
    }

    source = std::move(output);
}

int main()
{
    std::string source = "{ line1 { line2 { line3 } } }";
    FoldScopes(source, {"1.1", "1.1.1"});
    std::cout << source << "\n";
}