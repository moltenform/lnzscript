print('Running tests for namespace Internet.')

registerTest('Internet.ieFavorites');
Internet.ieFavorites(); Time.sleep(800);
assert(Window.exists('Organize Favorites'));
Window.close('Organize Favorites');

// Internet.ieClearTemporary works, at least with IE 7.

methods_list_summary_namespace('Internet');