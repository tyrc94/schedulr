let component = ReasonReact.statelessComponent("Main");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="Main">
      {ReasonReact.string("Welcome to Schedulr, where your nipples all have ice cubes")}
    </div>
};
