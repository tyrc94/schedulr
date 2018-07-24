[%bs.raw {|require('./App.css')|}];

type state = {
  isLoggedIn: bool
};

type action =
  | LogIn
;

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => { isLoggedIn: false },
  reducer: (action, state) => {
    switch (action) {
    | LogIn => ReasonReact.Update({ isLoggedIn: true })
    }
  },
  render: (self) =>
    <div className="App">
      <Header />

      <div className="app-body">
        {
          switch self.state.isLoggedIn {
          | true => <Main />
          | false => <Login />
          };
        }
      </div>
    </div>
};
