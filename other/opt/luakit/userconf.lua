-- My config for luakit.
--
local settings = require "settings"
settings.window.home_page = "www.duckduckgo.com"

local modes = require "modes"
modes.remap_binds(
	"normal",
	{
		-- new       old       removes the old binding(false)
		--{"O",      "t",      true},
	}
)

local engines = settings.window.search_engines
engines.aur          = "https://aur.archlinux.org/packages.php?O=0&K=%s&do_Search=Go"
engines.aw           = "https://wiki.archlinux.org/index.php/Special:Search?fulltext=Search&search=%s"
engines.googleseceng = "https://www.google.com/search?name=f&hl=en&q=%s"
engines.ddg          = "https://duckduckgo.com?q=%s&t=h_&ia=about"

-- Wiki.
engines.wwr          = "https://ru.wikipedia.org/wiki/%s"
engines.wwe          = "https://en.wikipedia.org/wiki/%s"
engines.wde          = "https://en.wiktionary.org/wiki/%s"
engines.wdr          = "https://ru.wiktionary.org/wiki/%s"
