module U = MaterialUi;
let s = ReactDOMRe.Style.make;

[%mui.withStyles
  "Styled"({
    paper: s(~flex="1", ())
  })
];

let component = ReasonReact.statelessComponent("Login");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <Styled render=(classes =>
      <U.Paper className=classes.paper>
        {ReasonReact.string("Login")}
      </U.Paper>
    )/>
};
