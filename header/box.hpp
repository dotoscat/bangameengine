#include <SFML/Graphics.hpp>
#include <lua5.1/lua.hpp>

namespace bange{
    
    class box{
        private:
            lua_State *vm;
            sf::RenderWindow *window;
            bool error;
        public:
            box(const char *);
            ~box();
            bool GetError();
            void Run();
    };
    
}
