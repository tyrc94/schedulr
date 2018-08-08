module U = MaterialUi;
let s = ReactDOMRe.Style.make;

[%mui.withStyles
  "Styled"({
    paper: s(~display="flex", ~flexDirection="column", ~flex="1", ()),
    container: s(~display="flex", ~flex="1", ~alignItems="center", ~justifyContent="center", ~padding="10px", ()),
  })
];

type state = {
  tab: int
};

type action =
  | UpdateTab(int)
;

let component = ReasonReact.reducerComponent("LoginSection");

let make = (~login, ~signup, _children) => {
  let signup_int = (signupRequest, self) => {
    signup(signupRequest)
      |> Js.Promise.then_ (
        () => self.ReasonReact.send(UpdateTab(0)) |> Js.Promise.resolve
      )
      |> ignore
  };

  {
    ...component,
    initialState: () => { tab: 0 },
    reducer: (action, _state) =>
      switch action {
      | UpdateTab(tab) => ReasonReact.Update({ tab: tab })
      },
    render: (self) =>
      <Styled render=(classes =>
        <U.Paper className=classes.paper>
            <U.Tabs centered=true value={self.state.tab} onChange={ (_e, tab) =>  self.send(UpdateTab(tab)) }>
              <U.Tab label=ReasonReact.string("Login") />
              <U.Tab label=ReasonReact.string("Signup") />
            </U.Tabs>

            <div className=classes.container>
              {
                switch self.state.tab {
                  | 1 => <Signup signup={self.handle(signup_int)} />
                  | _ => <Login login />
                };
              }
            </div>
        </U.Paper>
      )/>
  }
};
