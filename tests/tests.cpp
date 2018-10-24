#include "later.h"
#include "lest.hpp"

using namespace std;
using namespace tstraus;

const lest::test t[] =
{
    CASE("BasicTests" "[tstraus::Later]")
    {
        SETUP("BasicTests Setup")
        {
            bool b = false;

            SECTION("Chrono Detach")
            {
                Later::start(chrono::milliseconds(100), [](bool* b) {
                    *b = true;
                }, &b);

                EXPECT(b == false);
                this_thread::sleep_for(chrono::milliseconds(150));
                EXPECT(b == true);
            }

            SECTION("Millisecond Detach")
            {
                Later::start(100, [](bool* b) {
                    *b = true;
                }, &b);

                EXPECT(b == false);
                this_thread::sleep_for(chrono::milliseconds(150));
                EXPECT(b == true);
            }

            SECTION("Chrono Join")
            {
                auto t = Later::startP(chrono::milliseconds(100), [](bool* b) {
                    *b = true;
                }, &b);

                EXPECT(b == false);
                t->join();
                EXPECT(b == true);
            }

            SECTION("Millisecond Join")
            {
                auto t = Later::startP(100, [](bool* b) {
                    *b = true;
                }, &b);

                EXPECT(b == false);
                t->join();
                EXPECT(b == true);
            }
        }
    }
};

// run with '-p' to see each test
int main(int argc, char** argv)
{
    return lest::run(t, argc, argv);
}