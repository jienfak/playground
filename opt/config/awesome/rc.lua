-- user vars.
local xresources             = os.getenv("HOME").."/.Xresources"
local xkbdelay = 300
local xkbrate  = 60
local xkbcmd                = "setxkbmap -layout us,ru -option grp:alt_space_toogle"
local dvorakcmd             = "setxkbmap -layout us,ru -variant dvorak,  -option grp:alt_space_toggle"
local conf                  = (os.getenv("xdg_config_home") or os.getenv("HOME").."/.config").."/awesome/rc.lua"
local sh                    = os.getenv("shell")-- or "/usr/bin/zsh"
local nwcmd                 = "wicd-client -n"
local termcmd               = "termite"
local syscmd                = termcmd .. " -e htop"
local fmcmd                 = "xfe"
local ibcmd                 = "firefox"
local edcmd                 = "gvim"
local mpcmd                 = "vlc"
local vecmd                 = "openshot-qt"
local sndcmd                = "pavucontrol"
local hwcmd                 = "hardinfo"
local dawcmd                = "lmms"
local toggledvorakcmd  = 
                "if setxkbmap -print | grep dvorak ; then\n"..
                    xkbcmd.."\n"..
                "else\n"..
                    dvorakcmd.."\n"..
                "fi\n"

-- My library.
package.path = package.path..";"..os.getenv("S").."/lua/modules/?.lua" ;

-- Blackarch.
local addbamenu = true -- Should I add menu.
local bamaxmenu = 65   -- Maximum items in one column.
local balist = os.getenv("S").."/pl/5/utils/blackarch/utils.lst" -- Path to the list of utils.
local ba = require("blackarch")
local bamenu = {}
if addbamenu then
	ret = ba.awesome.getUtilList(balist, bamaxmenu)
	for _, cat in pairs(ret[2]) do
		table.insert(bamenu, cat)
	end
end
-- Standard awesome library.
local gears = require("gears")
local awful = require("awful")
require("awful.autofocus")
-- Widget and layout library.
local wibox = require("wibox")
-- Theme handling library.
local beautiful = require("beautiful")
-- Notification library.
local naughty = require("naughty")
local menubar = require("menubar")

-- local appmenu = pcall(require("appmenu"))
local hotkeys_popup = require("awful.hotkeys_popup").widget
require("awful.hotkeys_popup.keys")
-- local xdg_menu= require("archmenu")

-- Load Debian menu entries.
-- require("debian.menu")
local xdotool_mouse_move = false

-- {{{ Error handling
-- Check if awesome encountered an error during startup and fell back to
-- another config (This code will only ever execute for the fallback config).
if awesome.startup_errors then
	naughty.notify(
		{
			preset = naughty.config.presets.critical,
			title = "Oops, there were errors during startup!",
			text = awesome.startup_errors
		}
	)
end

-- Handle runtime errors after startup.
do
	local in_error = false
	awesome.connect_signal(
		"debug::error",
		function(err)
			-- Make sure we don't go into an endless error loop.
			if in_error then return end
			in_error = true

			naughty.notify(
				{
					preset = naughty.config.presets.critical,
					title = "Oops, an error happened!",
					text = tostring(err)
				}
			)
			in_error = false
		end
	)
end
-- }}}

-- {{{ Variable definitions.
-- Themes define colours, icons, font and wallpapers.
-- xresources, zenburn, default, sky
beautiful.init(awful.util.get_themes_dir().."xresources/theme.lua")

-- Default modkey.
-- Usually, Mod4 is the key with a logo between Control and Alt.
-- If you do not like this or do not have such a key,
-- I suggest you to remap Mod4 to another key using xmodmap or other tools.
-- However, you can use another modifier like Mod1, but it may interact with others.
modkey = "Mod4"

-- Table of layouts to cover with awful.layout.inc, order matters.
awful.layout.layouts = {
	awful.layout.suit.floating,
	awful.layout.suit.tile,
	awful.layout.suit.tile.left,
	awful.layout.suit.tile.bottom,
	awful.layout.suit.tile.top,
	awful.layout.suit.fair,
	awful.layout.suit.fair.horizontal,
	awful.layout.suit.spiral,
	awful.layout.suit.spiral.dwindle,
	awful.layout.suit.max,
	awful.layout.suit.max.fullscreen,
	awful.layout.suit.magnifier,
	awful.layout.suit.corner.nw,
	-- awful.layout.suit.corner.ne,
	-- awful.layout.suit.corner.sw,
	-- awful.layout.suit.corner.se,
}
-- }}}

-- {{{ Helper functions.
local function client_menu_toggle_fn()
	local instance = nil

	return function()
		if instance and instance.wibox.visible then
			instance:hide()
			instance = nil
		else
			instance = awful.menu.clients({ theme = { width = 250 } })
		end
	end
end
-- }}}
--
local function runOnce(cmd_arr)
    for _, cmd in ipairs(cmd_arr) do
        findme = cmd
        firstspace = cmd:find(" ")
        if firstspace then
            findme = cmd:sub(0, firstspace-1)
        end
        awful.spawn.with_shell(string.format("pgrep -u $USER -x %s > /dev/null || (%s)", findme, cmd))
    end
end

-- {{{ Menu.
-- Create a launcher widget and a main menu.
awesomemenu = {
		{
			"Hotkeys",
			function()
				return false, hotkeys_popup.show_help
			end
		},
		{
			"Manual",
			function()
				awful.util.spawn_with_shell(termcmd .. " -e 'man awesome'")
			end
		},
		{
			"Edit config",
			function()
				awful.util.spawn_with_shell(edcmd .." ".. conf)--awesome.conffile
			end
		},
		{
			"Restart WM",
			awesome.restart
		},
		{
			"Quit WM",
			function()
				awesome.quit()
			end
		},
		{
			"Switch user",
			"/usr/bin/dm-tool switch-to-greeter"
		}
	}
;

pcmenu = {
		{ "Shutdown",
			function()
				awful.util.spawn_with_shell("shutdown --poweroff now")
			end },
		{ "Reboot",
			function()
				awful.util.spawn_with_shell("shutdown --reboot now")
			end },
		{ "Halt",
			function()
				awful.util.spawn_with_shell("shutdown --halt now")
			end }
	}

mymenu = {
		-- { "Debian", debian.menu.Debian_menu.Debian },
		{ "Terminal", termcmd},
		{ "File manager", fmcmd},
		{ "Editor", edcmd },
		{ "Browser", function() awful.util.spawn_with_shell(ibcmd) end},
		{ "Sys. Stat.",
			function()
				awful.util.spawn_with_shell(termcmd.." -e "..syscmd)
			end},
		{ "HW info",
			function()
				awful.spawn(hwcmd)
			end },
		{ "NW Stat",
			function()
				awful.util.spawn_with_shell(nwcmd)
			end },
		{
			"Mus. Player",
			mpcmd
		},
	}

mainmenu = awful.menu(
		{
			items = {
				{ "Person", mymenu},
				{ "Awesome", awesomemenu, beautiful.awesome_icon },
				{ "Machine", pcmenu },
				{ "Blackarch", bamenu },
			}
		}
	)	
;

separator = wibox.widget.textbox(',') ;

launcher = awful.widget.launcher(
		{
			image = beautiful.awesome_icon,
			menu = mainmenu
		}
	)
;

-- Menu bar configuration.
menubar.utils.terminal = termcmd -- Set the terminal for applications that require it.
-- }}}

-- Keyboard map indicator and switcher.
kblayout = awful.widget.keyboardlayout()

-- {{{ Wibar.
-- Create a text clock widget.
textclock = wibox.widget.textclock()

-- Create battery widget.
--[[
batterywidget = wibox.widget.textbox()
batterywidget:set_text("|Battery|")
batterywidgettimer = timer({timeout = 5})
batterywidgettimer:connect_signal(
	"timeout",
	function()
		fh = assert(io.popen("acpi | cut -d, -f 2,3 -", "r")) ;
		batterywidget:set_text(fh:read("*1").."%")
		fh.close()
	end
)
batterywidgettimer:start()
--]]

-- Create a wibox for each screen and add it.
local taglist_buttons = awful.util.table.join(
		awful.button({ }, 1, function(t) t:view_only() end),
		awful.button(
			{modkey}, 1,
			function(t)
				if client.focus then
				client.focus:move_to_tag(t)
				end
			end
		),
		awful.button({}, 3, awful.tag.viewtoggle),
		awful.button(
			{ modkey }, 3,
			function(t)
				if client.focus then
					client.focus:toggle_tag(t)
				end
			end
		),
		awful.button({}, 4, function(t) awful.tag.viewnext(t.screen) end),
		awful.button({}, 5, function(t) awful.tag.viewprev(t.screen) end)
	)
;

local tasklist_buttons = awful.util.table.join(
		awful.button(
			{}, 1,
			function (c)
				if c == client.focus then
					c.minimized = true
				else
					-- Without this, the following
					-- :isvisible() makes no sense
					c.minimized = false
					if not c:isvisible() and c.first_tag then
						c.first_tag:view_only()
					end
					-- This will also un-minimize
					-- the client, if needed
					client.focus = c
					c:raise()
				end
			end
		),
		awful.button( {}, 3, client_menu_toggle_fn() ),
		awful.button(
			{}, 4,
			function()
				awful.client.focus.byidx(1)
			end
		),
		awful.button(
			{}, 5,
			function ()
				awful.client.focus.byidx(-1)
			end)
	)
;

local function set_wallpaper(s)
	-- Wallpaper.
	if beautiful.wallpaper then
		local wallpaper = beautiful.wallpaper
		-- If wallpaper is a function, call it with the screen.
		if type(wallpaper) == "function" then
			wallpaper = wallpaper(s)
		end
		gears.wallpaper.maximized(wallpaper, s, true)
	end
end

-- Re-set wallpaper when a screen's geometry changes (e.g. different resolution).
screen.connect_signal("property::geometry", set_wallpaper)

awful.screen.connect_for_each_screen(
	function(s)
		-- Wallpaper.
		set_wallpaper(s)

		-- Each screen has its own tag table.
		awful.tag({ "1", "2", "3", "4", "5", "6", "7", "8", "9" }, s, awful.layout.layouts[1])

		-- Create a promptbox for each screen
		s.promptbox = awful.widget.prompt()
		-- Create an imagebox widget which will contains an icon indicating which layout we're using.
		-- We need one layoutbox per screen.
		s.layoutbox = awful.widget.layoutbox(s)
		s.layoutbox:buttons(
			awful.util.table.join(
				awful.button({ }, 1, function () awful.layout.inc( 1) end),
				awful.button({ }, 3, function () awful.layout.inc(-1) end),
				awful.button({ }, 4, function () awful.layout.inc( 1) end),
				awful.button({ }, 5, function () awful.layout.inc(-1) end)
			)
		)
		-- Create a taglist widget.
		s.taglist = awful.widget.taglist(s, awful.widget.taglist.filter.all, taglist_buttons)

		-- Create a tasklist widget.
		s.tasklist = awful.widget.tasklist(s, awful.widget.tasklist.filter.currenttags, tasklist_buttons)

		-- Create the wibox.
		s.wibox = awful.wibar({ position = "top", screen = s })

		-- Add widgets to the wibox
		s.wibox:setup {
			layout = wibox.layout.align.horizontal,
			{ -- Left widgets.
				layout = wibox.layout.fixed.horizontal,
				launcher,
				s.taglist,
				s.promptbox,
			},
			s.tasklist,-- Middle widget.
			{ -- Right widgets.
				layout = wibox.layout.fixed.horizontal,
				kblayout,
				separator,
				awful.widget.watch('bash -c \'acpi -b | awk "/.*/ { print \\$4 \\$3}"\'', 15),
				wibox.widget.systray(),
				textclock,
				-- wibox.widget.textbox(' | '),
				separator,
				s.layoutbox,
			},
		}
	end
)
-- }}}

-- {{{ Mouse bindings
root.buttons(
	awful.util.table.join(
		awful.button({ }, 3, function () mainmenu:toggle() end),
		awful.button({ }, 4, awful.tag.viewnext),
		awful.button({ }, 5, awful.tag.viewprev)
	)
)
-- }}}

-- {{{ Key bindings
globalkeys = awful.util.table.join(
		awful.key({ modkey, "Control"}, "h",hotkeys_popup.show_help,
				{description=" - Show help.", group="awesome"}),
		--[[
		awful.key({ modkey, }, "Left", awful.tag.viewprev,
				{description = " - View previous.", group = "tag"}),
		awful.key({ modkey, }, "Right",awful.tag.viewnext,
				{description = " - View next.", group = "tag"}),
		awful.key({ modkey, }, "Escape", awful.tag.history.restore,
				{description = " - Go back.", group = "tag"}),
		--]]
		awful.key(
			{ modkey, }, "j",
			function()
				awful.client.focus.byidx(1)
				-- awful.util.spawn_with_shell("xdotool mousemove --window $(xdotool getactivewindow) 20 20")
			end,
			{description = " - Focus next by index.", group = "client"}
		),
		awful.key(
			{ modkey, }, "k",
			function()
				awful.client.focus.byidx(-1)
				-- awful.util.spawn_with_shell("xdotool mousemove --window $(xdotool getactivewindow) 20 20")
			end,
			{description = " - Focus previous by index.", group = "client"}
		),
		-- Dvorak.
		awful.key(
			{modkey, }, "a",
			function()
				awful.util.spawn_with_shell(toggledvorakcmd)
			end,
			{description = "- Toggle Dvorak.", group = "keyboard"}
		),
		awful.key(
			{ modkey, }, "w", function() mainmenu:show() end,
			{description = " - Show main menu.", group = "awesome"}
		),
		-- Layout manipulation
		awful.key(
			{ modkey, }, "e", function() awful.client.swap.byidx(1)	end,
			{description = " - Swap with next client by index.", group = "client"}
		),
		awful.key(
			{ modkey,  }, "o", function() awful.client.swap.byidx( -1)	end,
			{description = " - Swap with previous client by index.", group = "client"}
		),
		awful.key(
			{ modkey, "Control" }, "j", function() awful.screen.focus_relative(1) end,
			{description = " - Focus the next screen.", group = "screen"}
		),
		awful.key(
			{ modkey, "Control" }, "k", function () awful.screen.focus_relative(-1) end,
			{description = " - Focus the previous screen.", group = "screen"}
		),
		awful.key(
			{ modkey, }, "u", awful.client.urgent.jumpto,
			{description = " - Jump to urgent client.", group = "client"}
		),
		-- Terminal.
		awful.key(
			{ modkey, "Shift"}, "Return", function() awful.spawn(termcmd) end,
			{description = " - Open a terminal.", group = "launcher"}
		),
		awful.key(
			{modkey, "Shift"}, "b", function() awful.util.spawn_with_shell(ibcmd) end,
			{description=" - Open standard broswer.", group = "launcher"}
		),
		awful.key(
			{modkey, "Shift"}, "n", function() awful.spawn(nwcmd) end,
			{description=" - Open your network setting program.", group="launcher"}
		),
		-- File manager.
		awful.key(
			{modkey, "Shift"}, "f",
			function()
				awful.util.spawn_with_shell(fmcmd)
			end,
			{description = " - Open file manager", group = "launcher"}
		),
		-- Editor.
		awful.key(
			{modkey, "Shift"}, "i",
			function()
				awful.spawn(edcmd)
			end,
			{description = " - Open editor.", group = "launcher"}
		),
		-- Hardware info.
		awful.key(
			{modkey, "Shift"}, "h",
			function()
				awful.spawn(hwcmd)
			end,
			{description = " - Open hardware info prorgam.", group = "launcher"}
		),
		-- Music player.
		awful.key(
			{modkey, "Shift"}, "m",
			function()
				awful.spawn(mpcmd)
			end,
			{description = " - Open music player.", group="launcher"}
		),
		-- Sound control.
		awful.key(
			{modkey, "Shift"}, "s",
			function()
				awful.spawn(sndcmd)
			end,
			{description=" - Open your sound control program.", group="launcher"}
		),
		awful.key(
			{ modkey, "Shift"}, "v",
			function()
				awful.util.spawn_with_shell(vecmd)
			end,
			{description = " - Launch video editor.", group="launcher"}
		),
		awful.key(
			{ modkey, "Shift"}, "o",
			function()
				awful.util.spawn_with_shell(syscmd)
			end,
			{ description = " - Launch sys. stat. program.", group="launcher"}
		),
		awful.key(
			{ modkey, "Control", "Shift" }, "r", awesome.restart,
			{description = " - Reload awesome.", group = "awesome"}
		),
		awful.key(
			{ modkey, "Control", "Shift"}, "q", awesome.quit,
			{description = " - Quit awesome(!!!).", group = "awesome"}
		),
		awful.key(
			{ modkey, }, "l", function() awful.tag.incmwfact( 0.05) end,
			{description = " - Increase master width factor.", group = "layout"}
		),
		awful.key(
			{ modkey, }, "h", function() awful.tag.incmwfact(-0.05) end,
			{description = " - Decrease master width factor.", group = "layout"}
		),
		awful.key(
			{ modkey, }, "i", function() awful.tag.incnmaster( 1, nil, true) end,
			{description = " - Increase the number of master clients.", group = "layout"}
		),
		awful.key(
			{ modkey, }, "d", function() awful.tag.incnmaster(-1, nil, true) end,
			{description = " - Decrease the number of master clients.", group = "layout"}
		),
		awful.key(
			{ modkey, }, ".", function() awful.tag.incncol( 1, nil, true) end,
			{description = " - Increase the number of columns.", group = "layout"}),
		awful.key(
			{ modkey, },",", function() awful.tag.incncol(-1, nil, true)	end,
			{description = " - Decrease the number of columns.", group = "layout"}
		),
		awful.key({ modkey, }, "t", function() awful.layout.inc(1) end,
			{description = " - Select next.", group = "layout"}),
		awful.key({ modkey, }, "n", function() awful.layout.inc(-1) end,
			{description = " - Select previous.", group = "layout"}
		),
		awful.key(
			{modkey, }, "r",
			function()
				local c =awful.client.restore()
				if c then
					client.focus = c
					c:raise()
				end
			end,
			{description = " - Restore minimized.", group = "client"}
		),
		-- Prompt
		awful.key(
			{ modkey, "Shift"}, "r", function() awful.screen.focused().promptbox:run() end,
			{description = " - Run prompt.", group = "launcher"}
		),
		
		awful.key(
		--[[
			{ modkey }, "x",
			function()
				awful.prompt.run {
					prompt = "Run Lua code: ",
					textbox= awful.screen.focused().promptbox.widget,
					exe_callback = awful.util.eval,
					history_path = awful.util.get_cache_dir() .. "/history_eval"
				}
			end,
			{description = " - Lua execute prompt.", group = "awesome"}
			--]]
		),
		-- Menubar
		awful.key(
			{ modkey, "Shift"}, "p", function() menubar.show() end,
			{descript;on = " - Show the menubar.", group = "launcher"}
		)
	)

clientkeys = awful.util.table.join(
	awful.key(
		{ modkey,}, "f",
		function(c)
			c.fullscreen = not c.fullscreen
			c:raise()
		end,
		{description = " - Toggle fullscreen.", group = "client"}
	),
	awful.key({ modkey, }, "c",
		function(c)
			c:kill()
		end,
		{description = " - Close currently targeted window.", group = "client"}),
	awful.key(
		{ modkey, }, "space", awful.client.floating.toggle,
		{descriptio  = " - Toggle floating.", group = "client"}
	),
	awful.key(
		{ modkey, }, "Return",
		function(c)
			c:swap(awful.client.getmaster())
		end,
		{description = " - Move to master.", group = "client"}
	),
	--[[awful.key(
		{ modkey, }, "o",
		function(c)
			c:move_to_screen()
		end,
		{description = " - Move to screen.", group = "client"}
	), --]]
	awful.key(
		{ modkey, }, "v",
		function(c)
			c.ontop = not c.ontop
		end,
		{description = " - Toggle keep on top.", group = "client"}
	),
	awful.key(
		{ modkey, }, "x",
		function(c)
			-- The client currently has the input focus, so it cannot be
			-- minimized, since minimized clients can't have the focus.
			c.minimized = true
		end,
		{description = " - Minimize current window.", group = "client"}
	),
	awful.key(
		{ modkey, }, "m",
		function (c)
			c.maximized = not c.maximized
			c:raise()
		end ,
		{description = " - Maximize current window.", group = "client"}
	)
)

-- Bind all key numbers to tags.
-- Be careful: we use key codes to make it works on any keyboard layout.
-- This should map on the top row of your keyboard, usually 1 to 9.
for i = 1, 9 do
	globalkeys = awful.util.table.join(
			globalkeys,
			-- View tag only.
			awful.key(
				{ modkey }, "#" .. i + 9,
				function ()
					local screen = awful.screen.focused()
					local tag = screen.tags[i]
					if tag then
						tag:view_only()
					end
				end,
				{ description = " - View tag #"..i, group = "tag" }
			),
			-- Toggle tag display.
			awful.key(
				{ modkey, "Control" }, "#" .. i + 9,
				function()
					local screen = awful.screen.focused()
					local tag = screen.tags[i]
					if tag then
						awful.tag.viewtoggle(tag)
					end
				end,
				{description = " - Toggle tag #" .. i, group = "tag"}),
		-- Move client to tag.
		awful.key({ modkey, "Shift" }, "#" .. i + 9,
						function ()
							if client.focus then
								local tag = client.focus.screen.tags[i]
								if tag then
									client.focus:move_to_tag(tag)
								end
					 end
						end,
						{description = "move focused client to tag #"..i, group = "tag"}),
		-- Toggle tag on focused client.
		awful.key({ modkey, "Control", "Shift" }, "#" .. i + 9,
						function ()
							if client.focus then
								local tag = client.focus.screen.tags[i]
								if tag then
									client.focus:toggle_tag(tag)
								end
							end
						end,
						{description = " - Toggle focused client on tag #" .. i, group = "tag"})
	)
end

clientbuttons = awful.util.table.join(
		awful.button({ }, 1, function (c) client.focus = c; c:raise() end),
		awful.button({ modkey }, 1, awful.mouse.client.move),
		awful.button({ modkey }, 3, awful.mouse.client.resize)
	)
;

-- Set keys.
root.keys(globalkeys)
-- }}}

-- {{{ Rules.
-- Rules to apply to new clients (through the "manage" signal).
awful.rules.rules = {
	-- All clients will match this rule.
	{
		rule = {},
		properties = {
				border_width = beautiful.border_width,
				border_color = beautiful.border_normal,
				focus = awful.client.focus.filter,
				raise = true,
				keys = clientkeys,
				buttons = clientbuttons,
				screen = awful.screen.preferred,
				placement = awful.placement.no_overlap+awful.placement.no_offscreen
			}
		;
	},

	-- Floating clients.
	{ rule_any = {
		instance = {
				"DTA",-- Firefox addon DownThemAll.
				"copyq",-- Includes session name in class.
		},
		class = {
				"Arandr",
				"Gpick",
				"Kruler",
				"MessageWin",-- kalarm.
				"Sxiv",
				"Wpa_gui",
				"pinentry",
				"veromix",
				"xtightvncviewer"},

		name = {
				"Event Tester",-- xev.
		},
		role = {
				"AlarmWindow",-- Thunderbird's calendar.
				"pop-up", -- e.g. Google Chrome's (detached) Developer Tools.
		}
			}, properties = { floating = true }},

	-- Add titlebars to normal clients and dialogs
	{ rule_any = {type = { "normal", "dialog" }
			}, properties = { titlebars_enabled = true }
	},

	-- Set Firefox to always map on the tag named "2" on screen 1.
	-- { rule = { class = "Firefox" },
	--		 properties = { screen = 1, tag = "2" } },
}
-- }}}

-- {{{ Signals
-- Signal function to execute when a new client appears.
client.connect_signal(
	"manage",
	function (c)
		-- Set the windows at the slave,
		-- i.e. put it at the end of others instead of setting it master.
		-- if not awesome.startup then awful.client.setslave(c) end

		if awesome.startup and
				not c.size_hints.user_position
				and not c.size_hints.program_position then
			-- Prevent clients from being unreachable after screen count changes.
			awful.placement.no_offscreen(c)
		end
	end
)

-- Add a title bar if "titlebars_enabled" is set to true in the rules.
client.connect_signal(
	"request::titlebars",
	function(c)
		-- Buttons for the titlebar.
		local buttons = awful.util.table.join(
			awful.button({ }, 1, function()
				client.focus = c
				c:raise()
				awful.mouse.client.move(c)
			end),
			awful.button({ }, 3, function()
				client.focus = c
				c:raise()
				awful.mouse.client.resize(c)
			end)
		)

		awful.titlebar(c) : setup {
			{ -- Left.
				awful.titlebar.widget.iconwidget(c),
				buttons = buttons,
				layout = wibox.layout.fixed.horizontal
			},
			{ -- Middle.
				{ -- Title.
					align = "center",
					widget = awful.titlebar.widget.titlewidget(c)
				},
				buttons = buttons,
				layout = wibox.layout.flex.horizontal
			},
			{ -- Right.
				awful.titlebar.widget.floatingbutton(c),
				awful.titlebar.widget.maximizedbutton(c),
				awful.titlebar.widget.stickybutton(c),
				awful.titlebar.widget.ontopbutton(c),
				awful.titlebar.widget.closebutton(c),
				layout = wibox.layout.fixed.horizontal(),
				-- batterywidget
			},
			layout = wibox.layout.align.horizontal
		}
	end
)

-- Enable sloppy focus, so that focus follows mouse.
client.connect_signal(
	"mouse::enter",
	function(c)
		if awful.layout.get(c.screen) ~= awful.layout.suit.magnifier
				and awful.client.focus.filter(c) then
			client.focus = c
		end
	end
)

client.connect_signal("focus", function(c) c.border_color = beautiful.border_focus end)
client.connect_signal("unfocus", function(c) c.border_color = beautiful.border_normal end)
-- }}}

-- Autostart section.
awful.util.spawn_with_shell("xset r rate "..xkbdelay.." "..xkbrate)
awful.util.spawn_with_shell("xrdb -load "..xresources)
awful.util.spawn_with_shell(dvorakcmd)
awful.util.spawn_with_shell("[ -s ~/.Xmodmap ] && xmodmap ~/.Xmodmap")
runOnce({"yeahconsole"})
runOnce({"megasync"})
runOnce({"wicd-client -t"})
