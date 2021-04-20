#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>


void fill(std::vector<int>& v)
{
    for (size_t i = 0; i < v.size(); ++i)
    {
        v[i] = rand() % 5 + 1;
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

std::vector<int> multiply(const std::vector<int>& v1, const std::vector<int>& v2)
{
    std::vector<int> v;
    for (size_t i = 0; i < v1.size(); ++i)
    {
        v.push_back(v1[i] * v2[i]);
    }

    return v;
}

void write_in_file(const std::vector<int>& v)
{
    std::ofstream file("./vector.txt");
    std::ostream_iterator<int> output_iterator(file, " ");
    std::copy(v.begin(), v.end(), output_iterator);
    file.close();
}

int main(int argc, char* argv[])
{
    srand(unsigned(time(NULL)));

    size_t size = rand() % 10 + 1;
    std::vector<int> v1(size);
    std::vector<int> v2(size);

    fill(v1);
    fill(v2);

    std::cout << "first vector:\n\t";
    print(v1);
    std::cout << std::endl;

    std::cout << "second vector:\n\t";
    print(v2);
    std::cout << std::endl;

    auto v = multiply(v1, v2);

    std::cout << "third vector:\n\t";
    print(v);

    write_in_file(v);

    std::string fname = "vector.txt";

    pid_t pid = fork();
    if (pid == 0)
    {
        execl("./second", NULL, NULL);
        exit(0);
    }
    else if (pid > 0)
    {
        wait(NULL);
    }
    else
    {
        std::cerr << "Error: cannot fork.\n";
        return -1;
    }

    return 0;
}