import React from "react";
import "./ListCodeButton.css";

function ListCodeButton() {
  const data = [
    { id: 1, label: "Dòng 1", action: "Nội dung 1" },
    { id: 2, label: "Dòng 2", action: "Nội dung 2" },
    { id: 3, label: "Dòng 3", action: "Nội dung 3" },
    { id: 4, label: "Dòng 4", action: "Nội dung 4" },
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
