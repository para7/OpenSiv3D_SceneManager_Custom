
# include <Siv3D.hpp> // OpenSiv3D v0.2.8

# include "SceneManager2.cpp"

struct GameData
{
    Font font = Font(50);

    int32 score = 0;
};

using MyApp = SceneManager<String, GameData>;

struct Title : MyApp::Scene
{
    Title(const InitData& init)
        : IScene(init)
    {
        Print << getState();
    }

    void update() override
    {
        if (MouseL.down())
        {
            changeScene(U"Game", 2s);
        }
    }

    void draw() const override
    {
        getData().font(U"Title").drawAt(Window::BaseCenter());
    }
};

struct Game : MyApp::Scene
{
    Game(const InitData& init)
        : IScene(init)
    {
        Print << getState();

        getData().score = 0;
    }

    void update() override
    {
        if (MouseL.down())
        {
            changeScene(U"Result", 2s);
        }

        ++getData().score;
    }

    void draw() const override
    {
        getData().font(U"Game").drawAt(Window::BaseCenter());

        getData().font(getData().score).drawAt(Window::BaseCenter().movedBy(0, 60));
    }
};

struct Result : MyApp::Scene
{
    Result(const InitData& init)
        : IScene(init)
    {
        Print << getState();
    }

    void update() override
    {
        if (MouseL.down())
        {
            changeScene(U"Title", 2000);
        }
    }

    void draw() const override
    {
        getData().font(U"Result").drawAt(Window::BaseCenter());

        getData().font(getData().score).drawAt(Window::BaseCenter().movedBy(0, 60));
    }
};

void Main()
{
    const auto p = MakeShared<GameData>();

    MyApp manager;
    manager
        .add<Title>(U"Title")
        .add<Game>(U"Game")
        .add<Result>(U"Result");

    while (System::Update())
    {
        if (!manager.update())
        {
            break;
        }
    }
}
