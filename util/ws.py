import os, bottle, mimetypes

mimetypes.add_type('application/wasm','.wasm')

ROOT = '.'
REDIRECT_TO = 'index.html'

@bottle.get('/')
@bottle.get('/<path:path>')
@bottle.get('/<path:path>/')
def _(path = '.'):
    if not os.path.isdir(path):
        return bottle.static_file(path, ROOT)
    bottle.redirect(os.path.join('/',path,REDIRECT_TO))

