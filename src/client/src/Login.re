module U = MaterialUi;
let s = ReactDOMRe.Style.make;

[%mui.withStyles
  "Styled"({
    paper: s(~display="flex", ~flex="1", ~alignItems="center", ~justifyContent="center", ~padding="10px", ()),
    form: s(~width="25%", ()),
    textFields: s(~display="flex", ~margin="10px 0", ~flexDirection="column", ()),
    button: s(~float="right", ()),
  })
];

type state = {
  username: string,
  password: string
};

type action =
  | UpdateUsername(string)
  | UpdatePassword(string)
;

let updateUsername = (e, self) => {
  let e = e |> ReactEventRe.Form.target |> ReactDOMRe.domElementToObj;
  UpdateUsername(e##value) |> self.ReasonReact.send
}
let updatePassword = (e, self) => {
  let e = e |> ReactEventRe.Form.target |> ReactDOMRe.domElementToObj;
  UpdatePassword(e##value) |> self.ReasonReact.send
}

let component = ReasonReact.reducerComponent("Login");

let make = (~onSubmit, _children) => {
  ...component,
  initialState: () => { username: "", password: "" },
  reducer: (action, state) =>
    switch action {
    | UpdateUsername(username) => ReasonReact.Update({ ...state, username })
    | UpdatePassword(password) => ReasonReact.Update({ ...state, password })
    },
  render: (self) =>
    <Styled render=(classes =>
      <U.Paper className=classes.paper>
        <form className=classes.form>
          <div className=classes.textFields>
            <U.TextField type_="text" fullWidth=true placeholder="Username" label={ReasonReact.string("Username")} value={`String(self.state.username)} onChange={ self.handle(updateUsername) } />
            <U.TextField type_="password" fullWidth=true placeholder="Password" label={ReasonReact.string("Password")} value={`String(self.state.password)} onChange={ self.handle(updatePassword) } />
          </div>

          <U.Button className=classes.button variant=`Raised color=`Primary onClick={ (_e) => onSubmit(self.state.username, self.state.password) }>
            {ReasonReact.string("Log in")}
          </U.Button>

        </form>
      </U.Paper>
    )/>
};
