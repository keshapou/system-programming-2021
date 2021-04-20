#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <cstring>

std::vector<int> read_from_file(const std::string& fname)
{
    std::ifstream file(fname);
    std::istream_iterator<int> start(file), end;
    std::vector<int> v(start, end);
    file.close();

    return v;
}

std::string serialize(const std::vector<int>& v)
{
    std::string s = "";
    for (size_t i = 0; i < v.size(); ++i)
    {
        s += std::to_string(i);

        if (i != v.size()-1)
        {
            s += ' ';
        }
    }

    return s;
}

std::vector<int> deserialize(const std::string& s)
{
    std::string delimiter = " ";
    std::vector<int> v;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        v.push_back(std::stoi(token));
        std::cout << token << std::endl;
        // s.erase(0, pos + delimiter.length());
    }
    
    return v;
}

void fill(std::vector<std::vector<int>>& m)
{
    for (size_t i = 0; i < m.size(); ++i)
    {
        for (size_t j = 0; j < m[i].size(); ++j)
        {
            m[i][j] = rand() % 10 + 1;
        }
    }
}

void print(const std::vector<int>& v)
{
    for (auto i : v)
    {
        std::cout << i << ' ';
    }

    std::cout << std::endl;
}

void print(const std::vector<std::vector<int>>& m)
{
    for (size_t i = 0; i < m.size(); ++i)
    {
        std::cout << '\t';
        for (size_t j = 0; j < m[i].size(); ++j)
        {
            std::cout << m[i][j] << ' ';
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void write_in_file(const std::vector<int>& v)
{
    std::ofstream file("./matrix.txt");
    std::ostream_iterator<int> output_iterator(file, " ");
    std::copy(v.begin(), v.end(), output_iterator);
    file << '\n';
    file.close();
}

std::vector<std::vector<int>> multiply(const std::vector<int>& v, const std::vector<std::vector<int>>& m)
{
    std::vector<std::vector<int>> new_m;
    for (size_t i = 0; i < m.size(); ++i)
    {
        std::vector<int> row;
        pid_t pid = fork();
        if (pid == 0)
        {
            for (size_t j = 0; j < m[i].size(); ++j)
            {  
                row.push_back(v[j] * m[i][j]);
            }

            write_in_file(row);

            exit(0);
        }

        else if(pid > 0)
        {
            wait(NULL);
            new_m.push_back(read_from_file("./matrix.txt"));
        }
    }

    return new_m;
}

int main(int argc, char* argv[])
{
    srand(unsigned(time(NULL)));    
    std::vector<int> v = read_from_file("vector.txt");
    std::cout << "vector:\n\t";
    print(v);

    size_t rows = v.size();
    size_t columns = rand() % 5 + 1;
    std::vector<std::vector<int>> m(columns, std::vector<int>(rows));
    fill(m);
    std::cout << "\nmatrix:\n";
    print(m);

    auto new_m = multiply(v, m);
    std::cout << "\nnew matrix:\n";
    print(new_m);

    return 0;
}