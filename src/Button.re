[%bs.raw {|require('./Button.css')|}];

let component = ReasonReact.statelessComponent("Button");

let make = (~onClick, children) => {
  ...component,
  render: _self => <button onClick className="button"> ...children </button>,
};