#include"Project.hpp"
#include"Parser.hpp"
#include"Engine/Engine.hpp"

void	initEngine(Engine &engine)
{
	const int	screen_width = engine.getDisplayWidth();
	const int	screen_height = engine.getDisplayHeight();

	engine.addDisplay("Title_screen", {99, 194, 110, 0});

	engine.addDisplayButton("Title_screen",
		"Enter",
		engine.getRenderer(),
		"Enter",
		{0, 0, 0, 0},
		engine.getFont(),
		{ screen_width / 2 - 75, screen_height / 2 + 100, 150, 50 },
		{ 255, 255, 255, 0 },
		[&engine](){ engine.setCurrentDisplay("Test"); });

	engine.addDisplayButton("Title_screen",
		"Quit",
		engine.getRenderer(),
		"Quit",
		{0, 0, 0, 0},
		engine.getFont(),
		{ screen_width / 2 - 75, screen_height / 2 + 200, 150, 50 },
		{ 255, 255, 255, 0 },
		[&engine](){ engine.quit(); });

	engine.addDisplay("Test", {255, 0, 0, 0});
	engine.setCurrentDisplay("Title_screen");
}

int main(int argc, char **argv)
{
	(void)argc, (void)argv;
	try
	{
		// std::srand(time(0));

		// Parser	parser;

		// // parser.addArgToParse("-visual", "string");
		// parser.addArgToParse("-sessions", "int");
		// parser.addArgToParse("-save", "string");
		// // parser.addArgToParse("-learning", "string");
		// parser.addArgToParse("-load", "string");

		// auto args = parser.parse(argv, argc);

		// const size_t		sessions = args["-sessions"].empty() ? 10000 : std::atoi(args["-sessions"][0].c_str());

		// std::string const	load_filename = args["-load"].empty() ? "" : args["-load"][0];

		// std::string const	save_filename = args["-save"].empty() ? "" : args["-save"][0];

		// Project	project(10, 10, load_filename);

		// project.launchProject(sessions, save_filename, false, true);
		Engine	engine;

		initEngine(engine);
		engine.start();
		return(0);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

//state actuel : state debut de loop
//state next : state fin de loop

//donc pour update la q-table il faut garder en memoir le state actuel et futur


// 01010100	00000000 00010101 00000000
// 00000000 00010101 00000000 00000000

// 			S	W	R	G

// north	0	0	0	0

// south	1	1	1	0

// east		0	1	1	1

// west		0	0	0	0

// valeur = ordre apparition (0=premier, 1, 2, 3=dernier);
// si valeur (S ou R ou G) == valeur W -> y'a pas

// 000S00G0W

//	North			South		East			West
// 00 00 00 00 - 01 01 01 00 - 00 01 01 01 - 00 00 00 00
// S  W  R  G  - S  W  R  G  - S  W  R  G  - S  W  R  G