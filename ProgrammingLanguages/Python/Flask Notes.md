## setting a flask server up

- Make folder `mkdir project_name`.
- Create python notes using venv: `python3 -m venv env_name`.
- Activate the environment using `source env_name/bin/activate` (you must every time you go back to working on it).
- Install flask with pip `pip3 install flask`.
- OPTIONAL: install jedi for linting `pip3 install jedi`.
- create app and template files:
	- `touch app.py`.
	- `mkdir templates`.
- export environmental variables:
	- export the app: `export FLASK_APP=app`.
	- export the environment: `export FLASK_ENV=development` (NOTE: this is not what you do for a working app, only when developing).
- work on templates and app.
- to run, simply type the command: `flask run`.

## Working with flask in python

- flask uses an app instance to handle web requests. It does this by evoking a decorator on an object and pass it a route.
- the route is the website path and like file paths, the origin is `/`, with all other paths stemming from it.

### Paths

```python
from flask import Flask

app = Flask(__name__)

@app.route('/')
def hello():
	return '<h1>Hello, World!</h2>'
```

This example program demonstrates how the `app.route` decorator takes a function and converts it into a *Flask view* function. when we run the application, we get the URL `http://127.0.0.1:5000` which corresponds to the root `/`. When we open this in the browser we are shown to Hello, World! as heading as expected. To access web pages other than the origin we specify the pages route and another function:

```python
# ...

@app.route('/description/')
def description():
	return '<p>this page describes the web page.</p>'
```

To find this page we simply type `http://127.0.0.1:5000/description` and it shows us the description we typed.

### Dynamic Routes

Routes can be created on the fly to allow custom displaying of information. While it is uncommon for websites to make a user manually write the URL, for explanation we will. When typing in a custom URL, we use in-string variables. For example, if we want a page to display a string in lower case we could use a path like `/capitalize/<word>`:

```python
from markupsafe import escape # for safe displaying of text
# ...

@app.route('/capitalize/<word>')
def capitalize(word):
	return '<h1>{}</h1>'.format(escape(word.capitalize()))
```

Now, when we open the URL `http://127.0.0.1:5000/capitalize/hello` we see a web page with the heading Hello.

### Templates

Templates are HTML files that build a web page in a reusable and scaleable way. To use a template in code we use the render template method. For example, we create the file `./templates/hello.html`.

```html
<h1>Hello, World!</h1>
```

To import this html file into our web application in the code we return the render template we want to use.

```python
from flask import Flask, render_template, request

app = Flask(__name__)

@app.route('/hello')
def hello():
	return render_template('hello.html', template_folder='templates')
```

### Custom execution in templates (Jinja)

Custom python code can be executed from within html files using Jinja templates. Jinja templates are denoted with tags with `{% ... %}` brackets. Just like regular html they come in pairs and unlike python, code blocks are explicitly ended. Within a loop `{{ ... }}` denotes some item to be used. One example of Jinja templates is the for loop:

```html
{%for i in range(0, 10)%}
	<p>{{i}}</p>
{%endfor%}
```

### Requests

sometimes the user may want to input data to get a desired output.
