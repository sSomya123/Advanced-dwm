{ config, pkgs, ... }:

{
  home-manager.users.somya = {
    home.stateVersion = "24.05";
    home.enableNixpkgsReleaseCheck = false;
    home.packages = with pkgs; [
      git
      python3
      python3Packages.black
      python3Packages.flake8
      nodejs
      coc-pyright
    ];
    # Vim configuration
    programs.vim = {
    enable = true;
     plugins = with pkgs.vimPlugins; [
      vim-sensible
      nerdtree
      VimCompletesMe
      vim-airline
      vim-airline-themes
      SimpylFold
      vim-python-pep8-indent
      dracula-vim
      vim-devicons
      nerdcommenter
      vim-polyglot
      auto-pairs
      vim-fugitive
      jedi-vim
      nerdtree-git-plugin
      vim-nerdtree-syntax-highlight
      vim-github-dashboard
      vim-easy-align
      ultisnips
      vim-fireplace
      python-syntax
      coc-pyright
      catppuccin-vim
    ];
    extraConfig = ''
      set number
      syntax on
      set expandtab
      set autoindent
      set mouse=a
      set splitbelow splitright
      set cursorline
      set clipboard=unnamedplus
      set noshowmode
      set encoding=utf-8
      set foldmethod=indent
      set foldlevel=99
      nnoremap <space> za
      colorscheme catppuccin_mocha
      let g:airline#extensions#tabline#enabled = 1
      let g:airline_theme = 'dracula'
      let g:coc_global_extensions = ['coc-pyright']
      let g:ale_linters = {
        \   'python': ['flake8'],
      \}
      let g:ale_fixers = {
        \   'python': ['black'],
      \}
      augroup FileTypeSettings
      autocmd!
      autocmd FileType python setlocal tabstop=4 softtabstop=4 shiftwidth=4 textwidth=79 expandtab autoindent fileformat=unix
      autocmd FileType javascript,html,css setlocal tabstop=2 softtabstop=2 shiftwidth=2
      augroup END
      " NERDTree
      :autocmd VimEnter * NERDTree
      autocmd BufEnter * if (winnr('$') == 1 && exists('b:NERDTree') && b:NERDTree.isTabTree()) | q | endif
      map <C-n> :NERDTreeToggle<CR>
    '';
  };
    programs.kitty = {
      enable = true;
      font = {
        name = "JetBrainsMono Nerd Font";
        size = 10.0;
      };
      themeFile = "Dracula";

      settings = {
        background_opacity = "0.5";
        tab_bar_edge = "bottom";
        startup_session = "~/.config/kitty/startup.session";
        draw_minimal_borders = "yes";
        window_padding_width = 2;
        window_border_width = 0;
        titlebar_only = "yes";
        window_margin_width = 4;
        tab_bar_style = "powerline";
        detect_urls = "no";
        copy_on_select = "clipboard";
        strip_trailing_spaces = "smart";
        focus_follows_mouse = "yes";
        # hide_window_decorations = "yes";  # Uncomment if you want to hide window decorations
      };

      keybindings = {
        "ctrl+n" = "new_window";
        "ctrl+e" = "new_tab";
        "ctrl+shift+w" = "close_window";
        "ctrl+left" = "neighboring_window left";
        "ctrl+right" = "neighboring_window right";
        "ctrl+c" = "copy_to_clipboard";
        "ctrl+v" = "paste_from_clipboard";
        "shift+insert" = "paste_from_clipboard";
      };

    };
    programs.btop = {
       enable = true;
       settings = {
        theme_background = true;
        theme = "Dracula";
        vim_keys = false;
      };
    };
    services.mpd = {
      enable = true;
      musicDirectory = "/home/somya/music";
      extraConfig = ''
        # must specify one or more outputs in order to play audio!
        # (e.g. ALSA, PulseAudio, PipeWire), see next sections
        audio_output {
          type "pulse"
          name "PipeWire Output"
        }
      '';
    };
    programs.mpv = {
      enable = true;
      config = {

      };

    };
    programs.yazi = {
      enable = true;
      plugins = {
        full-border = ./yazi/plugins/full-border.yazi;
        mount = ./yazi/plugins/mount.yazi;
        nbpreview = ./yazi/plugins/nbpreview.yazi;
      };
      initLua = ./yazi/init.lua;
      flavors = {
        dracula = ./yazi/flavors/dracula.yazi;
      };

    };
     services.picom = {
      enable = true;
      backend = "glx";
      vSync = true;
      settings = {
        corner-radius = 10.0;
        rounded-corners-exclude = [
          #"window_type = 'normal'",
          "class_g = 'Rofi'"
          ];
        blur = {
          method = "dual_kawase";
          strength = 7;
          background = false;
          background-frame = false;
          background-fixed = false;
          opacity-rule = [ "90:class_g = 'kitty'" ];
        };
    };
  };
    programs.rofi = {
      enable = true;
      package = pkgs.rofi;     # or plain rofi if you're on X11
      plugins = [ pkgs.rofi-emoji
      pkgs.rofi-calc];
      theme = /home/somya/.config/rofi/theme.rasi;
    };

    xdg.configFile."yazi/yazi.toml".source = ./yazi/yazi.toml;  
    xdg.configFile."yazi/keymap.toml".source = ./yazi/keymap.toml;  
    xdg.configFile."yazi/init.lua".source = ./yazi/init.lua;  
    xdg.configFile."yazi/theme.toml".source = ./yazi/theme.toml;   
    programs.git = {
      enable = true;
      userName = "sSomya123";
      userEmail = "technologyindiatechnologyindia@gmail.com";
    };
    home.sessionVariables = {
    };

  };
}

