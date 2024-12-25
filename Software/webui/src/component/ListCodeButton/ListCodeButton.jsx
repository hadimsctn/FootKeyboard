import React from "react";
import "./ListCodeButton.css";

function ListCodeButton() {
  const data = [
    { id: 1, label: "Ctrl", action: "80" },
    { id: 2, label: "Shift", action: "81" },
    { id: 3, label: "Alt", action: "82" },
    { id: 4, label: "Key Up Arrow", action: "DA" },
    { id: 5, label: "Key Down Arrow", action: "D9" },

  ];

  return (
    <div className="table-container">
      <h2 className="table-title">Bảng mã</h2>
      <table className="styled-table">
        <thead>
          <tr>
            <th>Nút bấm</th>
            <th>Code</th>
          </tr>
        </thead>
        <tbody>
          {data.map((row, index) => (
            <tr key={row.id} className={index % 2 === 0 ? "even" : "odd"}>
              <td>{row.label}</td>
              <td>{row.action}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
}

export default ListCodeButton;
