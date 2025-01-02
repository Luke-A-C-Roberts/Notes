Pheonix Request Lifecycles
===========================

------------------------------------------------------------------------------------------
Sources: 
- [https://hexdocs.pm/phoenix/request_lifecycle.html](hexdocs)
- [https://www.youtube.com/watch?v=vlKEB600NBE](youtube)

------------------------------------------------------------------------------------------


An address corresponds to a HTTP request to a service, i.e. a pheonix application. The request is made of a verb (web request) and a path.

| Address                            | Verb | Path         |
| ---------------------------------- | ---- | ------------ |
| https://localhost:4000/            | GET  | /            | 
| https://localhost:4000/hello       | GET  | /hello       |
| https://localhost:4000/hello/world | GET  | /hello/world |

Web apps handle requests by mapping each verb/path pair into a specific part of the application (completed by the router in Pheonix). To add a new page, a new route must be added, found in "lib/*_web/router.ex" where * is the name of the project.

In a new pheonix project, in "router/*_web/router.ex", setting up the root (a.k.a the index) page of the application is achieved using a `get` macro. Here for example the project is called `Hello`.

```elixir
scope "/", HelloWeb do
  pipe_through :browser
  get "/", PageController, :home
end
```

Home refers to a controller function in "lib/*_web/page_controller.ex" called `home/2` which handles the http request for the root page of the application. In "router.ex" this is refered to as `:home`.

If we want to create a new page we create a new GET request, refering to a new path branching from the root "/", a new get macro is written. For example if we want to create a page using "/hello":

```elixir
  get "/hello", HelloController, :index
```

To add a variable as part of the address the `:atom` syntax can be used. For example to let the application say hello to a specific person, after the "/hello" subdomain we can add a variable for a messenger (`:messenger`). The get statement looks like:
```elixir
  get "/hello/:messenger", HelloController, :show
```

The idea is if we type in the URL "localhost:4000/hello/Luke" then "Luke" is assigned to `:messenger` and a defined `show` function in the controller layer will handle the request.

## Controllers

Controllers make actions happen, for instance the controller function for `:index` is defined in a controller file: "lib/hello_web/controllers/hello_controller.ex".

The code to define `:index` is as follows.

```elixir
defmodule HelloWeb.HelloController do
  use HelloWeb, :controller

  def index(conn, _params) do
    render(conn, :index)
  end 
end
```

Here `conn` refers all of the request data and `params` contains any request parameters although if its not needed its better to call it `_params`.

Another controller function is `show`, is ususally used to pass information to rendering. for example if we want to pass the `:messenger` variable from parameters to the `render` function, then the code is as follows:

```elixir
  def show(conn, %{"messenger" => messenger}) do
    render(conn, :show, messenger: messenger)
  end
```

## Views

Views are the presentation layer of pheonix, which help render HTML. To create dynamically generated pages, pheonix uses templates.

To create a page for the hello controller, we create a "_html.ex" file along side it, in this case "lib/hello_web/controllers/hello_html.ex"

Templates can be done within "_html.ex" files or by loading a "index.html.heex"file, contained within a subdirectory with the same name as the view file. For example "lib/hello_web/controllers/hello_html/index.html.heex"

If we want to define a template in the "_html.ex" file then we define another function for `:index` in the module.

```elixir
defmodule HelloWeb.HelloHTML do
  use HelloWeb, :html

  def index(assigns) do
    ~H"""
    Hello!
    """
  end
end
```

If we instead want to load a `.heex` file we use the `embed_templates` macro along with the path to the template subdirectory.

```elixir
defmodule HelloWeb.HelloHTML do
  use HelloWeb, :html

  embed_templates "hello_html"
end
```

```heex
<section>
  <h2>Hello World, from Pheonix!</h2>
</section>
```

If we want to include a variable during rendering, we can use the `<%= %>` syntax. To include `:messenger`, in the `.heex` file it would be:

```heex
<section>
  <h2>Hello World, from <%= @messenger %>!</h2>
</section>
```

The URL "localhost:4000/hello/Luke" would read "Hello World, from Luke!".

## The Endpoint

HTTP requests enter through the application endpoint, defined in "lib/*_web/endpoint.ex". The endpoint utilises `Plug` which manages the whole web application. `plug` (lowecase) is used to allocate and handle request processing to a specific task. For example to load the router module, `plug HelloWeb.Router` allows the endpoint to delegate request processing. 
When we launch the web server the first thing that is ran is the endpoint, using a webserver, either **cowboy** or **bandit** depending on the project configuration. The endpoint is accessed at the devices IP address.

### The endpoint file

Multiple `plug` calls are used to handle various parts of the web application.

- `Plug.Static` is used to handle requests dealing with static assets such as css and media like images, sounds etc.

- `Pheonix.LiveDashboard.RequestLogger` handles request logging for the web page.

- `Plug.Telemetry` handles web page telemetry.

- `Plug.Parsers` handles JSON parsing for APIs.

## Lifecycle of requests layers.

It takes sevaral layers to go from a request to displaying HTML.

- `Pheonix.Endpoint`: Where all requests begin their journey.
- `Pheonix.Router`: Where controllers are dispatched in order to handle verb/path.
- `Pheonix.Controller`: Retrieves request information and interact to the buisiness domain, then prepare data for presentation.
- view: handles structured data from the controller and converts it to HTML for display.
