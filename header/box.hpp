#include <SFML/Graphics.hpp>
#include <lua5.1/lua.hpp>

namespace bange{
    
    class box{
        private:
            lua_State *vm;
            sf::RenderWindow *window;
        public:
            box();
            box(const char *);
            ~box();
            void Run();
        protected:
            void Initialize();
    };
    
}
